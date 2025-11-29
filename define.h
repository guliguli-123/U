#define un using namespace
#define str(x) #x
#define i int
#define l long
#define _f float
#define d double
#define b bool
#define ch char
#define au auto
#define HINST HINSTANCE
#define LPS LPSTR
#define con const
#define re return
#define end ;
un std end
#define out cout <<
#define in cin >>
#define n << endl
#define deffun(type, name, ...) type name(__VA_ARGS__) {
#define loopstart {
#define ifstart {
#define endfun } 
#define endloop } 
#define endif }
#define add +
#define sub -
#define mul *
#define div /
#define nextcin >>
#define nextout <<
#define forloop(number, name) for(i name=0; name<number; name++) 
#define forin(elements) for(auto &el : elements)
#define endforin }
#define whileloop(boolean) while(boolean) 
#define el else
#define elif else if
#define T true
#define F false
#define defmain deffun(i, main, )
#define cmdlinemain deffun(i, main, i argc, ch* argv[])
#define winmain deffun(i WINAPI, WinMain, HINST hInstance, HINST hPrevInstance, LPS lpCmdLine, i nCmdShow)
#define ptr(type) type*
#define stru(name) struct name 
#define strustart {
#define endstru }
#define defclass(name) class name 
#define classstart {
#define endclass }
#define callback(type, name, ...) typedef type (* name )(__VA_ARGS__);
#define lambda(type, ...) [](__VA_ARGS__) -> type {
#define endlambda }
#define pri private:
#define pub public:
#define pro protected:
#define autotypefunction(type, name, arg) auto name(arg) -> type {
#define autotypefunctionend }
#define extend :
#define def #
#define di #define
#define ext exit(0)
#define throwerror throw
#define error(err) runtime_error(err)
#define _try try {
#define _catch } catch(const exception &e) {
#define _endcatch }
#define windows_try __try {
#define windows_catch(_err) } __except( _err ) {
#define windows_endcatch }
#define asm __asm {
#define endasm }
#define every bits/stdc++
#define tag(name) name :
#define go(name) goto name

#define command(com) system(com)
#define taskkill(name) system(("taskkill /f /im " + to_string(#name)).data())
