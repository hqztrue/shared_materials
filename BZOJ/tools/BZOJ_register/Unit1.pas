unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Memo1: TMemo;
    Button2: TButton;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure register_;
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
procedure press(c:longint);
  begin
  keybd_event(c,0,0,0);
  sleep(50);
  end;
procedure press_s(s:string);
var
  i,l:longint;
  begin
  l:=length(s);
  for i:=1 to l do
    begin
    keybd_event(ord(s[i]),0,0,0);
    //Form1.memo1.lines.add(inttostr(ord(s[i]))+' '+string(s[i]));
    sleep(50);
    end;
  end;
procedure TForm1.register_();
var
i,id:longint;
f:textfile;
begin
winexec('cmd /c start http://www.lydsy.com/JudgeOnline/registerpage.php',0);
sleep(500);
for i:=1 to 10 do press(9);
id:=random(10000);
assignfile(f,'user_id\JJJJJJ'+inttostr(id)+'.txt');rewrite(f);closefile(f);
//press_s('SILLYHOOK'+inttostr(id));
press_s('JJJJJJ'+inttostr(id));
memo1.lines.add(inttostr(id));
press(9);
press(9);
press_s('123456');
press(9);
press_s('123456');
press(9);
press(9);
press(9);
//press(10);press(13);
keybd_event(VK_RETURN,0,0,0);
keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
sleep(200);
for i:=1 to 10 do press(9);
sleep(100);
keybd_event(VK_RETURN,0,0,0);
keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);
end;
procedure TForm1.Button1Click(Sender: TObject);
var
  i:longint;
  begin
  for i:=1 to 1000 do
    begin
    register_;
    {if (i mod 5=0) then begin
      winexec('taskkill /f /im chrome.exe',0);
      sleep(1000);
      end;}
    end;
  end;

procedure TForm1.FormCreate(Sender: TObject);
begin
randomize;
memo1.clear();
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
sleep(5000);
press(10);press(13);
end;

end.
