# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.27
# 

Name:       powerdevil

# >> macros
# << macros

Summary:    Manages the power consumption settings of a Plasma Shell
Version:    5.1.0
Release:    1
Group:      System/Base
License:    GPLv2+
URL:        http://www.kde.org
Source0:    %{name}-%{version}.tar.xz
Source100:  powerdevil.yaml
Source101:  powerdevil-rpmlintrc
Requires:   kf5-filesystem
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  pkgconfig(Qt5Xml)
BuildRequires:  pkgconfig(Qt5Network)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Widgets)
BuildRequires:  pkgconfig(Qt5Concurrent)
BuildRequires:  pkgconfig(Qt5Test)
BuildRequires:  pkgconfig(Qt5PrintSupport)
BuildRequires:  pkgconfig(Qt5X11Extras)
BuildRequires:  pkgconfig(systemd)
BuildRequires:  pkgconfig(upower-glib)
BuildRequires:  pkgconfig(xcb)
BuildRequires:  pkgconfig(xrandr)
BuildRequires:  kf5-rpm-macros
BuildRequires:  extra-cmake-modules
BuildRequires:  qt5-tools
BuildRequires:  xcb-util-keysyms-devel
BuildRequires:  xcb-util-image-devel
BuildRequires:  xcb-util-wm-devel
BuildRequires:  kauth-devel
BuildRequires:  kidletime-devel
BuildRequires:  kconfig-devel
BuildRequires:  solid-devel
BuildRequires:  ki18n-devel
BuildRequires:  kglobalaccel-devel
BuildRequires:  kio-devel
BuildRequires:  kwindowsystem-devel
BuildRequires:  plasma-devel
BuildRequires:  knotifyconfig-devel
BuildRequires:  kdelibs4support-devel
BuildRequires:  plasma-workspace-devel
BuildRequires:  chrpath

%description
Manages the power consumption settings of a Plasma Shell.


%package kcm
Summary:    Power management configuration module for Plasma
Group:      System/Base
Requires:   %{name} = %{version}-%{release}

%description kcm
Power management configuration module for Plasma.


%package doc
Summary:    Documentation and user manuals for %{name}
Group:      Documentation
BuildArch:  noarch
Requires:   %{name} = %{version}-%{release}

%description doc
Documentation and user manuals for %{name}


%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
%kf5_make
# << build pre



# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
%kf5_make_install
# << install pre

# >> install post
# Don't bother with -devel
rm -f %{buildroot}%{_kf5_libdir}/libpowerdevil{configcommonprivate,core,ui}.so
# << install post

%files
%defattr(-,root,root,-)
%doc COPYING
%{_kf5_sysconfdir}/dbus-1/system.d/org.kde.powerdevil.backlighthelper.conf
%{_kf5_libdir}/libpowerdevilconfigcommonprivate.so.*
%{_kf5_libdir}/libpowerdevilcore.so.*
%{_kf5_libdir}/libpowerdevilui.so.*
%{_kf5_libdir}/libexec/kauth/backlighthelper
%{_datadir}/dbus-1/system-services/org.kde.powerdevil.backlighthelper.service
%{_datadir}/knotifications5/powerdevil.notifyrc
%{_datadir}/polkit-1/actions/org.kde.powerdevil.backlighthelper.policy
%{_kf5_servicesdir}/kded/*.desktop
# >> files
# << files

%files kcm
%defattr(-,root,root,-)
%{_kf5_plugindir}/*
%{_kf5_servicesdir}/*.desktop
%{_kf5_servicetypesdir}/*.desktop
# >> files kcm
# << files kcm

%files doc
%defattr(-,root,root,-)
%{_kf5_htmldir}/en/*
# >> files doc
# << files doc
