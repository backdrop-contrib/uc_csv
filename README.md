# Ubercart CSV

The purpose of this module is to export orders from an Ubercart store in a manner that
can be read by any spreadsheet program such as Libre Office or Microsoft Excel.

You can create any number of reports to export certain criteria. More granular criteria
can be programmed later if there is demand for such a feature. Please provide feedback if
this is the case.

The date of last export and last order id exported are tracked. Each report is incremental so
that when you do an export, any previously exported items are excluded from the report.

The exported CSV does contain field headers.

## Installation

- Install this module using the [official Backdrop CMS instructions](https://backdropcms.org/guide/modules).

## Configuration and Usage

Details can be configured at Store > CSV Export (admin/store/export).

More details may be found (or added) in the [Wiki](https://github.com/backdrop-contrib/uc_csv/wiki)

## Issues

Bugs and Feature requests should be reported in the [Issue Queue](https://github.com/backdrop-contrib/uc_csv/issues)

## Current Maintainers

- [Laryn Kragt Bakker](https://github.com/laryn), [CEDC.org](https://CEDC.org)
- Co-maintainers and collaboration welcome!

## Credits

- Ported to Backdrop by [Laryn Kragt Bakker](https://github.com/laryn), [CEDC.org](https://CEDC.org)
- Created for Drupal by [Michael R. Bagnall](https://www.drupal.org/u/elusivemind).

## License

This project is GPL-2.0 (or later) software. See the LICENSE.txt file in this directory for
complete text.
