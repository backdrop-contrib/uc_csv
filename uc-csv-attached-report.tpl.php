--<?php echo $boundary;?>

Content-Type: text/plain; charset="iso-8859-1"
Content-Transfer-Encoding: 7bit

Greetings;

Here is an attachment of an export.

Report Name: <?php echo $report->report_name;?>


--<?php echo $boundary;?>

Content-Disposition: attachment; filename="<?php echo $filename;?>"; size="<?php echo $filesize;?>;
Content-Transfer-Encoding: base64

<?php echo chunk_split(base64_encode($contents)); ?>
