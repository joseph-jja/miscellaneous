%define name godura
%define version 0.6.1
%define release 1
%define packager Joseph Acosta <joeja@mindspring.com>
%define builddir /home/joeja/rpmbuild

Summary: A simple text editor designed especially for spec files.
Name: %{name}
Version: %{version}
Release: %{release}
Copyright: GPL
Group: Applications/Editors
Source: %{name}-%{version}.tar.gz
Buildroot: %{builddir}/tmp/%{name}-build
URL: http://www.mindspring.com/~joeja/programs.html

%description
     This is a simple text editor that has a few features geared to makeing rpms a little easier.

%prep

%setup

%build
./configure
make

%install
cd src
install -D godura $RPM_BUILD_ROOT/usr/local/bin/

%files 
/usr/local/bin/godura

%doc README
%doc TODO
%doc KNOWNBUGS
%doc INSTALL

%clean 
rm -rf %{builddir}/BUILD/%{name}-%{version}
rm -rf $RPM_BUILD_ROOT

%changelog
