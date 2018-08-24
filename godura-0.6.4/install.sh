#!/bin/sh

# this install script is for Linux ONLY!!!!!
if [ `uname` != "Linux" ]; then
    echo "This install script is for Linux ONLY!!"
	echo "If you are reading this message then you are not using Linux!!!" 
    exit
fi 
# here we need to check first to make sure the directories all exist
# we should also prompt the user to make sure that this is where they 
# want to have the directories

if [ ! -e ~/rpmbuild ]; then
    echo "Running mkdir  ~/rpmbuild/{BUILD,SPECS,SOURCES,SRPMS,RPMS/{i386,noarch,i586,i686,athlon}}"
    mkdir -p ~/rpmbuild/{BUILD,SPECS,SOURCES,SRPMS,RPMS/{i386,noarch,i586,i686,athlon}}
fi

export topdir="%_topdir "`echo $HOME`/rpmbuild
export buildroot="%_buildroot "`echo $HOME`/rpmbuild/tmp

# here we check to see if there is a rpmmacros file in the home directory
# if there is we need to check to see if these values are in it
if [ ! -e $HOME/.rpmmacros ]; then
    echo $topdir > $HOME/.rpmmacros
    echo $buildroot >> $HOME/.rpmmacros
else
    export TR=`grep topdir $HOME/.rpmmacros`
    export BR=`grep buildroot $HOME/.rpmmacros`
#    if [ !  ]; then
        echo $topdir > $HOME/.rpmmacros
#    fi
#    if [ !  ]; then
        echo $buildroot >> $HOME/.rpmmacros
#    fi
fi

if [ -e godura.h ]; then
    export VER=`grep -i version godura.h|awk '{print $3}'`
fi

# here we build the spec file that is used for installation of godura
echo "%define name godura" > godura.spec
echo "%define version $VER" >> godura.spec
echo "%define release 1" >> godura.spec
echo "%define packager Joseph Acosta <joeja@mindspring.com>" >> godura.spec
echo "" >> godura.spec
echo "Summary: A simple text editor designed especially for spec files." >> godura.spec
echo "Name: %{name}" >> godura.spec
echo "Version: %{version}" >> godura.spec
echo "Release: %{release}" >> godura.spec
echo "Copyright: GPL" >> godura.spec
echo "Group: Applications/Editors" >> godura.spec
echo "Source: %{name}-%{version}.tar.gz" >> godura.spec
echo "Buildroot: /home/joeja/rpmbuild/tmp/%{name}-build" >> godura.spec
echo "URL: http://www.mindspring.com/~joeja/programs.html" >> godura.spec
echo "" >> godura.spec
echo "%description" >> godura.spec
echo "     This is a simple text editor that has a few features geared to makeing rpms a little easier." >> godura.spec 
echo "" >> godura.spec
echo "%prep" >> godura.spec
echo "" >> godura.spec
echo "%setup" >> godura.spec
echo "" >> godura.spec
echo "%build" >> godura.spec
echo "make" >> godura.spec
echo "" >> godura.spec
echo "%install" >> godura.spec
echo "install -D godura \$RPM_BUILD_ROOT/usr/local/bin/" >> godura.spec
echo "" >> godura.spec
echo "%files " >> godura.spec
echo "/usr/local/bin/godura" >> godura.spec
echo "" >> godura.spec
echo "%doc README" >> godura.spec
echo "%doc TODO" >> godura.spec
echo "%doc KNOWNBUGS" >> godura.spec
echo "%doc INSTALL" >> godura.spec
echo "" >> godura.spec
echo "%clean " >> godura.spec
echo "rm -rf $HOME/rpmbuild/BUILD/%{name}-%{version}" >> godura.spec
echo "rm -rf \$RPM_BUILD_ROOT" >> godura.spec
echo "" >> godura.spec
echo "%changelog" >> godura.spec
