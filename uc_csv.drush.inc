<?php

/**
 * Implementation of hook_drush_command().
 */
function uc_csv_drush_command() {
  $items = array();
  $items['uc-csv-export'] = array(
    'description' => dt('Run an export and place the exported file in the specified location, or in the same place where the command is called if unspecified.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'arguments' => array(
      'of' => dt('The relative path and file name to where you want the export file placed.'),
    ),
    'options' => array(
      'sd' => array(
        'description' => dt('The start date of when the export should take place (yyyy-mm-dd)'),
        'example-value' => '2014-10-01',
      ),
      'ed' => array(
        'description' => dt('The end date of when the export should end (yyyy-mm-dd)'),
        'example-value' => '2014-10-31',
      ),
      'ie' => array(
        'description' => dt('Ignore state of previously exported entries (export all)'),
        'example-value' => 'true',
      ),
      'email' => array(
        'description' => dt('Optional: The email address to send the finished report to.'),
        'example-value' => '--email=test@testing.com',
      ),
      'examples' => array(
        'uc-csv-export export_file.csv --sd=2014-10-01 --ed=2014-10-31 --ie=true',
        'uc-csv-export --sd=2014-10-01 --ed=2014-10-31 --ie=true --email=test@testing.com',
      ),
      'aliases' => array('ucce'),  
    ),
  );
  
  $items['uc-csv-export-report'] = array(
    'description' => 'Run an export of a specific report (by id)',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'arguments' => array(
      'of' => dt('The relative path and file name to where you want the export file placed.'),
      'id' => dt('The machine ID of the report to be generated'),
    ),
    'examples' => array(
      'export report 1' => 'uc-csv-export-report export_file.csv 1',
    ),
    'aliases' => array('ucer'),  
  );
  
  return $items;
}

/**
 * Implementation of drush_hook_COMMAND_validate().
 */
function drush_uc_csv_uc_csv_export_validate($of = NULL) {
  // check to make sure we have been provided a proper output file for dumping our
  // export to
  if (empty($of)) {
    drush_set_error(dt('You did not specify a file name and location for your export file.'));
  }
  
  // check the dates to make sure they are in the proper format
  $start_date = drush_get_option('sd');
  $end_date = drush_get_option('ed');
  if (!empty($start_date) && strlen($start_date) != 10) {
    drush_set_error(dt('Your start date is not the proper length to be valid.'));
  }
  if (!empty($end_date) && strlen($end_date) != 10)  {
    drush_set_error(dt('Your end date is not the proper length to be valid.'));
  }
  
  foreach (array($start_date, $end_date) as $date) {
    list($year, $month, $day) = explode('-', $date);
    if (checkdate($month, $day, $year) === FALSE) {
      drush_set_error(dt('One of your specified dates was invalid. Please double check your date and try again.'));
    }
  }
  
  // Now we generate a report object and get the report
  $report = new stdClass();
  
}

/**
 * Drush export cvs file from ubercart command callback
 *
 * We need to basically create a report on the fly and create a report object to send
 * to the fuction which generates this
 */
function drush_uc_csv_export($of = NULL) {
  $form = $form_state = array();

  // Simulate a report by generating the report object used by the creation process.
  // TODO: make all currently assigned items (save track) selectable as options in
  // the command line.
  $report = new stdClass();
  $report->volatile = TRUE;
  $report->shipping_address = TRUE;
  $report->billing_address = TRUE;
  $report->products = TRUE;
  $report->track = FALSE;
  $report->start_date = drush_get_option('sd');
  $report->end_date = drush_get_option('ed');
  $report->file_type = 'csv';
  $report->report_name = (!empty($of)) ? $of : 'exported_report';
  $report->email_address = drush_get_option('email');
  $report->email_enable = (!empty($report->email_address)) ? TRUE : FALSE; 

  // For now we will assume all statuses are to be exported as part of this report.
  // We may want to make it in the future so you can select which statuses are to
  // be exported, but that could be confusing.
  $result = db_query("SELECT order_status_id
                      FROM {uc_order_statuses}
                      ORDER BY weight ASC"); 
  while($sdata = $result->fetchObject()) {
    $statuses[] = $sdata->order_status_id;
  }
  $report->statuses = serialize($statuses);

  // Generate the report
  $data = uc_csv_select_report_to_export_submit($form, $form_state, $report);
  
  if ($report->email_enable == FALSE) {
    // Save the report to our specified location or right here if nothing selected.
    _uc_csv_save_report($report, $data['contents'], $report->report_name);
  }
}

/**
 * Make sure that we have a valid report id
 */
function drush_uc_csv_export_report_validate($of = NULL, $id = NULL) {
  // If they have not specified a file name then all bets are off
  if (empty($of)) {
    drush_set_error(dt('You must specify a file name for your report.'));
    return FALSE;
  }
  // if they haven't specified a report id, then all bets are off, but we shouldn't
  // get this since they are presented a list
  if (is_numeric($id)) {
    $result = db_query("SELECT * FROM {uc_csv_reports} WHERE rid=:rid;", array(':rid' => $id));
    $report = $result->fetchObject();
    if (empty($report->report_name) || !$report->report_name) {
      drush_set_error(dt('There is no report with an id of ' . $id));
      return FALSE;
    }
  }    
}

/**
 * Do the report
 *
 * This follows the model used by the web interface, but allows for command line execution
 */
function drush_uc_csv_export_report($of, $id = NULL) {
  // if the id is null, then present a list of available reports to export and have them
  // select from that list
  if (empty($id)) {
    // Get a list of all of the available reports
    $options = array();
    $result = db_query('SELECT * from {uc_csv_reports} ORDER BY report_name ASC');
    while ($rdata = $result->fetchObject()) {
      $options[$rdata->rid] = $rdata->report_name;
    }
    
    $choice = drush_choice($options, dt('Which report do you wish to export?'));
    $form_state = array();
    $form_state['values']['rid'] = $choice;
    $data = uc_csv_select_report_to_export_submit(array(), $form_state);
  }
  else {
    $form_state = array();
    $form_state['values']['rid'] = $id;
    $data = uc_csv_select_report_to_export_submit(array(), $form_state);
  }
  
  $of = drush_get_option('of');
  if (!empty($of)) {
    _uc_csv_save_report($data['report'], $data['contents'], $of);
  }
}
