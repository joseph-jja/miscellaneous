# This file was automagically generated with spec-gen 
# By Joseph Acosta 
Summary: An uptime Applet for GNOME
Name: GUTime
Version: 0.0.6
Release: 1
Copyright: GPL
Group: User Interface/Desktop
Packager: Joseph Acosta
%description
This is a simple uptime applet.

It is designed for the GNOME panel and is untested elsewhere.
Read the LICENSE file that you should have gotton with this
program.

This is known to work with Fedora Core 2 and contains code that may
not make it work on other platforms or operating systems.

This program requires the GTK+ libraries to be installed and is known to
work with GTK+ 2.x . Earlier version may work, but I make no promises about
that.

This program also requires the GNOME libs.  It is known to work with GNOME
version 2.6.  If you do not have these libraries installed DO NOT
send me bug reports.

%prep

%setup 

%build
make

%install
make install

%files


