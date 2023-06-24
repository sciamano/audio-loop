Name:		audio-loop
Version:	1.1.0
Release:	1.1
Summary:	Qt app that playes sound in a loop

License:	GPL-3.0
Source:		%{name}_%{version}.orig.tar.gz

BuildRequires:	cmake
BuildRequires:	desktop-file-utils
BuildRequires:	gcc-c++
BuildRequires:	hicolor-icon-theme
BuildRequires:	pkgconfig
BuildRequires:	pkgconfig(Qt6Core)
BuildRequires:	pkgconfig(Qt6Multimedia)
BuildRequires:	pkgconfig(Qt6Test)
BuildRequires:	pkgconfig(Qt6Widgets)

%description
Qt app that playes sound in a loop

%prep
%autosetup

%build
%cmake -DCMAKE_SKIP_RPATH=ON -DAPP_VERSION=%{version} -DCMAKE_INSTALL_DOCDIR=%{_docdir}/%{name}
%cmake_build

%install
%cmake_install
desktop-file-validate %{buildroot}/%{_datadir}/applications/audio-loop.desktop

%files
%{_bindir}/%{name}
%{_docdir}/%{name}/
%{_datadir}/applications/audio-loop.desktop
%{_datadir}/icons/hicolor/128x128/apps/audio-loop.png
%{_datadir}/tone.wav
