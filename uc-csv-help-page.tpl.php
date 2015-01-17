<h1>Ubercart CSV Export (uc_csv) Help</h1>
This is a module to facilitate the export of order data from Ubercart. It exports only 
main Ubercart fields and does not export custom fields or fields provided by other
modules. There are several ways to generate reports and several means to get reports.
<br /><br />

<ol>
  <li>Defined Reports & Manual Downloaded Exports</li>
  <li>Defined Reports & Manual Emailed Exports</li>
  <li>Defined Reports & Cron Based Emailed Reports</li>
  <li>Defined Reports & Drush Exported Reports</li>
  <li>Reports Generated via the Drush Command Line Tool.</li>
</ol>

<br />

<h2>Defining A Report</h2>
Reports are defined by going to the <?php echo $create_new_report; ?> option and selecting
which options you would like to include in your report. In addition, you can select which
report statuses you wish to export, how orders should be ordered, the type of export,
tracking of orders and if you wish to have the report emailed when generated.<br /><br />

Report tracking means that each order will only be exported once in so that each export
is an addition to the previous export and will only export orders that have been placed
since the previous export.<br /><br />

<h2>Downloading Reports</h2>
Downloaded reports from the administrative menu will occur instantly. You select the report
you wish to download and it will export and download right to your computer.<br /><br />

<h2>Emailed Reports</h2>
Selecting this option will send scheduled exports to the email address of your choosing.
You can have different email addresses for different reports if desired.<br /><br />

<h2>Cron Exports</h2>
Select the interval with which reports are exported via the Drupal cron mechanism. Note 
that this setting also depends on the frequency with which your cron task runs. If you
select a report per hour, but your cron only runs every three hours, then you will get
a report every three hours and so on.<br /><br />

<h2>Drush Exports</h2>
There are two kinds of drush exports. There is one where you can run the export on one
of your reports and you can also run an export on a report defined with drush options.
Note that exports made with the latter option cannot be tracked. The current drush options
for reports are as follows:<br /><br />

<b>drush uc-csv-export <output file> [options]</b><br />
Exports a custom report based on the options specified at runtime.<br />
<ul>
  <li><b>start</b> - The start date of the export.</li>
  <li><b>end</b> - The end date of the export.</li>
  <li><b>shipping-address</b> - Include the shipping address on exported orders.</li>
  <li><b>billing-address</b> - Include the billinbg address on exported orders.</li>
  <li><b>products</b> - Include the list of products on exported orders</li>
  <li><b>file-type</b> - Set the type of file to be exported (csv/xls). Defaults to csv.</li>
  <li><b>order-by</b> - How to order the report (order-id/last-name). Defaults to order-id.</li>
  <li><b>email</b> - the email address to send the report to (causes output file argument to be ignored)</li>
</ul><br />

<b>drush uc-csv-export-report <output file> <report id></b><br />
Export a pre-defined report.<br />
<ul>
  <li><b>ignore</b> - Ignore the state oof previously exported entries (export all entries).</li>
</ul>

<br /><br /><br />
