unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls,winprocs;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Edit1: TEdit;
    Button2: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}
function work(id:longint):boolean;
var
str,s1:string;
p:Tpoint;
i:longint;
begin
if not fileexists('sol\'+inttostr(id)+'.cpp') then
  begin work:=false; exit;end;
winexec(pansichar('cmd /c start sol\'+inttostr(id)+'.cpp'),SW_SHOWNORMAL);
sleep(1000);
//for i:=1 to 2000000000 do;
keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0);
keybd_event(ord('A'), MapVirtualKey(ord('A'), 0), 0, 0);
keybd_event(ord('A'), MapVirtualKey(ord('A'), 0), KEYEVENTF_KEYUP, 0);
keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0);

keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0);
keybd_event(ord('C'), MapVirtualKey(ord('C'), 0), 0, 0);
keybd_event(ord('C'), MapVirtualKey(ord('C'), 0), KEYEVENTF_KEYUP, 0);
keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0);
//exit;
sleep(2000);
str:='cmd /c start http://www.lydsy.com/JudgeOnline/submitpage.php?id=';
winexec(pansichar(str+inttostr(id)),SW_SHOWNORMAL);
sleep(2000);
keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0);
keybd_event(ord('V'), MapVirtualKey(ord('V'), 0), 0, 0);
keybd_event(ord('V'), MapVirtualKey(ord('V'), 0), KEYEVENTF_KEYUP, 0);
keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0);
sleep(2000);
setcursorpos(608,631);
mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
work:=true;
end;

procedure TForm1.Button1Click(Sender: TObject);
var i,cnt:longint;
begin
//work(strtoint(edit1.Text));
winexec(pansichar('cmd /c start http://www.lydsy.com/JudgeOnline/status.php'),SW_SHOWNORMAL);
winexec(pansichar('cmd /c start http://www.lydsy.com/JudgeOnline/status.php'),SW_SHOWNORMAL);
sleep(1000);
cnt:=0;
for i:=1000 to 3500 do
  begin
  edit1.Text:=inttostr(i);
  if (work(i))then begin
    inc(cnt);
    if (cnt=1)then begin
      cnt:=0;
      winexec(pansichar('cmd /c taskkill /f /im notepad.exe'),SW_SHOWNORMAL);
      keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0);
      keybd_event(ord('W'), MapVirtualKey(ord('W'), 0), 0, 0);
      keybd_event(ord('W'), MapVirtualKey(ord('W'), 0), KEYEVENTF_KEYUP, 0);
      keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0);
      sleep(500);
      keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0);
      keybd_event(ord('W'), MapVirtualKey(ord('W'), 0), 0, 0);
      keybd_event(ord('W'), MapVirtualKey(ord('W'), 0), KEYEVENTF_KEYUP, 0);
      keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0);

      winexec(pansichar('cmd /c start http://www.lydsy.com/JudgeOnline/status.php'),SW_SHOWNORMAL);
      //winexec(pansichar('cmd /c taskkill /f /im chrome.exe'),SW_SHOWNORMAL);
      end;
    sleep(4000);
    end;
  end;
winexec(pansichar('cmd /c echo orz_flower|cmd.exe&pause'),SW_SHOWNORMAL);
//showmessage('orz flower!!!');
//MessageBox(Form1.Handle,'MessageBox','orz flower',MB_ICONINFORMATION+MB_OkCancel)
end;
procedure TForm1.Button2Click(Sender: TObject);
begin
showmessage('orz flower!!!');
//winexec(pansichar('cmd /c taskkill /f /im notepad.exe'),SW_SHOWNORMAL);
//winexec(pansichar('cmd /c taskkill /f /im chrome.exe'),SW_SHOWNORMAL);
{sleep(1000);
keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), 0, 0);
keybd_event(ord('A'), MapVirtualKey(ord('A'), 0), 0, 0);
keybd_event(ord('A'), MapVirtualKey(ord('A'), 0), KEYEVENTF_KEYUP, 0);
keybd_event(VK_CONTROL, MapVirtualKey(VK_CONTROL, 0), KEYEVENTF_KEYUP, 0); }
end;

end.
