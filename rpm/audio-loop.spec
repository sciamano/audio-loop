Name:           audio-loop
Version:        1.1.0
Release:        1.1
Summary:        qt app that playes sound in a loop

License:        GPL-3.0
Source:         %{name}_%{version}.orig.tar.gz

BuildRequires:  cmake
BuildRequires:  gcc-c++
BuildRequires:	pkgconfig
BuildRequires:	pkgconfig(Qt6Core)
BuildRequires:	pkgconfig(Qt6Multimedia)
BuildRequires:	pkgconfig(Qt6Test)
BuildRequires:	pkgconfig(Qt6Widgets)

%description
qt app that playes sound in a loop

%prep
%autosetup

%build
%cmake -DAPP_VERSION=%{version} -DCMAKE_INSTALL_DOCDIR=%{_docdir}
%cmake_build

%install
%cmake_install

%files
%{_bindir}/%{name}
%{_docdir}/%{name}/README.md
%{_datadir}/applications/
%{_datadir}/icons/
%{_datadir}/tone.wav
