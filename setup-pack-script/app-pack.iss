; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "GunshipVPet虚拟桌宠"
#define MyAppVersion "2.0-alpha1"
#define MyAppPublisher "NJU EL 武装直升机组"
#define MyAppURL "https://github.com/Positron114514/GunShipVPet"
#define MyAppExeName "GunshipVPet.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{0EAAA45B-0C66-471C-AD48-2823AFDFE6A5}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\GunshipVPet
DisableProgramGroupPage=yes
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputDir=E:\Codes\Qt\GunshipVPetApp
OutputBaseFilename="setup-GunshipVPet-{#MyAppVersion}"
SetupIconFile=E:\Codes\Qt\GunshipVPet\resources\icons\setup-logo.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "E:\Codes\Qt\GunshipVPetApp\app\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "E:\Codes\Qt\GunshipVPetApp\app\*"; Excludes: "E:\Codes\Qt\GunshipVPetApp\app\resources\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "E:\Codes\Qt\GunshipVPetApp\app\resources\*"; DestDir: "{userdocs}\GunshipVPet\resources"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Code]
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);

begin
  if CurUninstallStep = usUninstall then
    if MsgBox('您是否要删除用户设置？', mbConfirmation, MB_YESNO) = IDYES then
      DelTree(ExpandConstant('{userdocs}\GunshipVPet'), True, True, True);
end;

[UninstallDelete]
;Type: filesandordirs; Name: "{userdocs}\GunshipVPet\*"
