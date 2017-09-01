# SambaSimpleClient
Samba simple client. GUI frontend for mount.

## Build
Requires QT Creator for QT.5.

## Installation
Build samba-simple-client-qt-gui and copy it with samba-simple-client-qt and to /usr/local/bin.

## Execution
May be executed from every path by running samba-simple-client-qt.

## Program concept, rules
1. No config files. If you want to store settings in a config file, fork and write an advanced samba client.
2. Allow to specify samba most popular settings.
3. Use /mnt/samba directory for all shares.

## Server syntax:
\\\\ip\_number\Share\_name

## Licensing
In case of any fork the developer needs to provide information about the author: name and email (Piotr Zieliński, rozbujnik@gmail.com).

## TODO
* Help button
* support server smb:// syntax.
* Unmounting should remove directory from /mnt/samba/


