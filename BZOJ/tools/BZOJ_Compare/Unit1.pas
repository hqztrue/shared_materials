unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, XPMan,idhttp, IdBaseComponent, IdComponent,
  IdTCPConnection, IdTCPClient,shellapi;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    Edit1: TEdit;
    Label2: TLabel;
    Edit2: TEdit;
    XPManifest1: TXPManifest;
    BitBtn1: TBitBtn;
    IdHTTP1: TIdHTTP;
    edt3: TEdit;
    mmo1: TMemo;
    mmo2: TMemo;
    lbl1: TLabel;
    lbl2: TLabel;
    lbl3: TLabel;
    lbl4: TLabel;
    lbl5: TLabel;
    lbl6: TLabel;
    mmo3: TMemo;
    lbl7: TLabel;
    lbl8: TLabel;
    lbl9: TLabel;
    lbl10: TLabel;
    lbl11: TLabel;
    btn1: TButton;
    dlgSave1: TSaveDialog;
    btn2: TButton;
    btn3: TButton;
    lbl12: TLabel;
    lbl13: TLabel;
    lbl14: TLabel;
    btn4: TButton;
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure gethtml(s:string);
    procedure clear();
    procedure btn1Click(Sender: TObject);
    procedure btn2Click(Sender: TObject);
    procedure btn3Click(Sender: TObject);
    procedure btn4Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
  arr=array[0..10005]of longint;
var
  Form1: TForm1;
  a,b,same:arr;
  c:array[0..1000005]of char;
implementation

{$R *.dfm}
procedure TForm1.clear();
begin
  //edit1.clear();edit2.clear();
  lbl3.Caption:='';lbl6.Caption:='';
  lbl9.Caption:='';lbl10.Caption:='';
  edt3.clear();
  mmo1.clear();mmo2.clear();mmo3.clear();
  lbl12.Caption:='sum=0';lbl13.Caption:='sum=0';lbl14.Caption:='sum=0';
end;
procedure TForm1.gethtml(s:string);
var
  MyStream:TMemoryStream;
begin
  try
    Edt3.Text:='';
    MyStream:=TMemoryStream.Create;
    IdHTTP1.Get('http://www.lydsy.com/JudgeOnline/userinfo.php?user='+s,MyStream);
    MyStream.SaveToFile(ExtractFilePath(Application.ExeName)+'html\'+s+'.txt');
  finally
    MyStream.Free;
    Edt3.Text:=IdHTTP1.Response.Server+':  '+IdHTTP1.Response.ResponseText;
  end;
end;
procedure get(s:string;var a:arr;var len:longint);
var
  f:text;
  l,i:longint;
  begin
  //showmessage(inttostr(len));
  assignfile(f,ExtractFilePath(Application.ExeName)+'html\'+s+'.txt');reset(f);
  l:=0;
  while not eof(f) do
    begin
    l:=l+1;
    read(f,c[l]);
    end;
  closefile(f);
  //showmessage('l='+inttostr(l));
  len:=0;
  for i:=2 to l-5 do
    if (c[i-1]='p')and(c[i]='(')and(c[i+1]>='0')and(c[i+1]<='9')
      and(c[i+2]>='0')and(c[i+2]<='9')
      and(c[i+3]>='0')and(c[i+3]<='9')
      and(c[i+4]>='0')and(c[i+4]<='9')
      and(c[i+5]=')')then
        begin
        len:=len+1;
        a[len]:=(ord(c[i+1])-ord('0'))*1000+
          (ord(c[i+2])-ord('0'))*100+
          (ord(c[i+3])-ord('0'))*10+
          (ord(c[i+4])-ord('0'))*1;
        end;
  //showmessage(inttostr(len));
  end;
procedure print1(var a:arr;len:longint;mmo:TMemo);
var
  i:longint;
  out:ansistring;
begin
  mmo.clear();
  //showmessage(inttostr(len));
  for i:=1 to len do
    begin
    //mmo.Lines.add(inttostr(a[i]));
    out:=out+inttostr(a[i])+' ';
    //if (strlen(out)>
    end;
  mmo.Lines.add(out);
end;
procedure TForm1.BitBtn1Click(Sender: TObject);
var
  lena,lenb,ha,hb,i,suma,sumb,sumsame:longint;
  outa,outb,outsame:ansistring;
  begin
  clear();
  if ((edit1.text='') or (edit2.text='') or (edit1.text='solved') or (edit2.text='can_AC'))then exit;
  lbl3.Caption:=edit1.text;lbl6.Caption:=edit2.text;
  lbl9.Caption:=lbl3.Caption;lbl10.Caption:=lbl6.Caption;
  Form1.Caption:=edit1.text+' VS '+edit2.Text;
  gethtml(edit1.text);
  gethtml(edit2.text);
  get(edit1.text,a,lena);
  //print1(a,lena,mmo1);
  get(edit2.text,b,lenb);
  //print1(b,lenb,mmo2);
  outa:='';outb:='';outsame:='';
  suma:=0;sumb:=0;sumsame:=0;
  ha:=1;hb:=1;
  for i:=1 to lena+lenb do
    begin
    if (ha<=lena)and(hb<=lenb)and(a[ha]=b[hb])then begin
      outsame:=outsame+inttostr(a[ha])+' ';inc(ha);inc(hb);inc(sumsame);
      continue;
    end;
    if (ha<=lena)and((hb>lenb)or(a[ha]<b[hb]))then begin
      outa:=outa+inttostr(a[ha])+' ';inc(ha);inc(suma);
      continue;
    end;
    if (hb<=lenb)and((ha>lena)or(b[hb]<a[ha]))then begin
      outb:=outb+inttostr(b[hb])+' ';inc(hb);inc(sumb);
      continue;
    end;
    end;
  mmo1.Lines.add(outa);lbl12.Caption:='sum='+inttostr(suma)+'+'+inttostr(sumsame)+'='+inttostr(suma+sumsame);
  mmo2.Lines.add(outb);lbl13.Caption:='sum='+inttostr(sumb)+'+'+inttostr(sumsame)+'='+inttostr(sumb+sumsame);
  mmo3.Lines.add(outsame);lbl14.Caption:='sum='+inttostr(sumsame);
  end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  clear();
  if (not fileexists(ExtractFilePath(Application.ExeName)+'html'))then begin
    Createdirectory(pansichar(ExtractFilePath(Application.ExeName)+'html'),nil);
    end;
end;

procedure TForm1.btn1Click(Sender: TObject);
var
  ff:textfile;
begin
  dlgsave1.Execute;
  if dlgsave1.filename='' then exit;
  dlgsave1.filename:=dlgsave1.filename;
  assignfile(ff,dlgsave1.filename);rewrite(ff);
  writeln(ff,'Problems only '+edit1.text+' accepted:'+'   '+lbl12.Caption);
  writeln(ff,mmo1.lines.text);
  writeln(ff);
  writeln(ff,'Problems only '+edit2.text+' accepted:'+'   '+lbl13.Caption);
  writeln(ff,mmo2.lines.text);
  writeln(ff);
  writeln(ff,'Problems both '+edit1.text+' and '+edit2.text+' accepted:'+'   '+lbl14.Caption);
  writeln(ff,mmo3.lines.text);
  writeln(ff);
  closefile(ff);
end;

procedure TForm1.btn2Click(Sender: TObject);
begin
  edit1.text:='from file';
end;

procedure TForm1.btn3Click(Sender: TObject);
var
  lena,lenb,ha,hb,i,suma,sumb,sumsame:longint;
  outa,outb,outsame:ansistring;
begin
  clear();edit1.text:='solved';
  if ((edit1.text='') or (edit2.text='') or (edit2.text='can_AC'))then exit;
  lbl3.Caption:=edit1.text;lbl6.Caption:=edit2.text;
  lbl9.Caption:=lbl3.Caption;lbl10.Caption:=lbl6.Caption;
  Form1.Caption:=edit1.text+' VS '+edit2.Text;
  gethtml(edit2.text);
  get(edit1.text,a,lena);
  //print1(a,lena,mmo1);
  get(edit2.text,b,lenb);
  //print1(b,lenb,mmo2);
  outa:='';outb:='';outsame:='';
  suma:=0;sumb:=0;sumsame:=0;
  ha:=1;hb:=1;
  for i:=1 to lena+lenb do
    begin
    if (ha<=lena)and(hb<=lenb)and(a[ha]=b[hb])then begin
      outsame:=outsame+inttostr(a[ha])+' ';inc(ha);inc(hb);inc(sumsame);
      continue;
    end;
    if (ha<=lena)and((hb>lenb)or(a[ha]<b[hb]))then begin
      outa:=outa+inttostr(a[ha])+' ';inc(ha);inc(suma);
      continue;
    end;
    if (hb<=lenb)and((ha>lena)or(b[hb]<a[ha]))then begin
      outb:=outb+inttostr(b[hb])+' ';inc(hb);inc(sumb);
      continue;
    end;
    end;
  mmo1.Lines.add(outa);lbl12.Caption:='sum='+inttostr(suma)+'+'+inttostr(sumsame)+'='+inttostr(suma+sumsame);
  mmo2.Lines.add(outb);lbl13.Caption:='sum='+inttostr(sumb)+'+'+inttostr(sumsame)+'='+inttostr(sumb+sumsame);
  mmo3.Lines.add(outsame);lbl14.Caption:='sum='+inttostr(sumsame);
end;
procedure TForm1.btn4Click(Sender: TObject);
var
  lena,lenb,ha,hb,i,suma,sumb,sumsame:longint;
  outa,outb,outsame:ansistring;
begin
  clear();edit1.text:='solved';edit2.text:='can_AC';
  if ((edit1.text='') or (edit2.text=''))then exit;
  lbl3.Caption:=edit1.text;lbl6.Caption:=edit2.text;
  lbl9.Caption:=lbl3.Caption;lbl10.Caption:=lbl6.Caption;
  Form1.Caption:=edit1.text+' VS '+edit2.Text;
  //gethtml(edit2.text);
  get(edit1.text,a,lena);
  //print1(a,lena,mmo1);
  get(edit2.text,b,lenb);
  //print1(b,lenb,mmo2);
  outa:='';outb:='';outsame:='';
  suma:=0;sumb:=0;sumsame:=0;
  ha:=1;hb:=1;
  for i:=1 to lena+lenb do
    begin
    if (ha<=lena)and(hb<=lenb)and(a[ha]=b[hb])then begin
      outsame:=outsame+inttostr(a[ha])+' ';inc(ha);inc(hb);inc(sumsame);
      continue;
    end;
    if (ha<=lena)and((hb>lenb)or(a[ha]<b[hb]))then begin
      outa:=outa+inttostr(a[ha])+' ';inc(ha);inc(suma);
      continue;
    end;
    if (hb<=lenb)and((ha>lena)or(b[hb]<a[ha]))then begin
      outb:=outb+inttostr(b[hb])+' ';inc(hb);inc(sumb);
      continue;
    end;
    end;
  mmo1.Lines.add(outa);lbl12.Caption:='sum='+inttostr(suma)+'+'+inttostr(sumsame)+'='+inttostr(suma+sumsame);
  mmo2.Lines.add(outb);lbl13.Caption:='sum='+inttostr(sumb)+'+'+inttostr(sumsame)+'='+inttostr(sumb+sumsame);
  mmo3.Lines.add(outsame);lbl14.Caption:='sum='+inttostr(sumsame);
end;
end.
