// In FreePascal 3.0.0+, a Delphi-like UnicodeString type is supported.
// String/(P)Char map to UnicodeString/(P)WideChar if {$MODE DelphiUnicode}
// or {$MODESWITCH UnicodeStrings} is used.  We are enabling them so Indy
// uses the same Unicode logic in Delphi 2009+ and FreePascal 3.0.0+ and
// reduces IFDEFs (in particular, STRING_UNICODE_MISMATCH, see further below).
// However, FreePascal's RTL is largely not UnicodeString-enabled yet, so we
// will have to deal with that as needed...
{$MODE DelphiUnicode}

//note that we may need further defines for widget types depending on
//what we do and what platforms we support in FPC.
//I'll let Marco think about that one.
{$IFDEF UNIX}
  //In Linux for I386, you can choose between a Kylix-libc API or
  //the standard RTL Unix API.  Just pass -dKYLIXCOMPAT to the FPC compiler.
  //I will see what I can do about the Makefile.
  {$IF DEFINED(LINUX) AND DEFINED(KYLIXCOMPAT) AND DEFINED(CPUI386)}
    {$UNDEF USE_BASEUNIX}
  {$ELSE}
    {$DEFINE USE_BASEUNIX}
  {$IFEND}
  {$IFDEF USE_BASEUNIX}
    {$UNDEF KYLIXCOMPAT}
  {$ENDIF}
{$ENDIF}

// detect compiler version

{$MACRO ON} // must be on in order to use versioning macros

{$IF FPC_FULLVERSION < 30000}
  {$Warning Unsupported compiler version detected!}
{$IFEND}

{$DEFINE FPC_3_0_0_OR_ABOVE}

// FreePascal's RTL mimic D7's RTL
// TODO: replace these with appropriate HAS_xxx defines instead...
{.$DEFINE DCC_7)
{.$DEFINE DELPHI_7)
{.$DEFINE DCC_7_OR_ABOVE)

// available features

{.$DEFINE HAS_RemoveFreeNotification}
{.$DEFINE HAS_IInterface}
{.$DEFINE HAS_TSelectionEditor}
{.$DEFINE HAS_SYMBOL_PLATFORM}
{.$DEFINE HAS_UNIT_PLATFORM}
{$DEFINE USE_INLINE}
{$DEFINE USE_CLASSINLINE}
{$DEFINE USE_TBitBtn} //use Bit Buttons instead of Buttons
{$DEFINE FPC_REINTRODUCE_BUG}
{$DEFINE FPC_CIRCULAR_BUG}
{$DEFINE NO_REDECLARE}
{$DEFINE BYTE_COMPARE_SETS}
{$DEFINE HAS_QWord}
{$DEFINE HAS_PQWord}
{.$DEFINE HAS_PUInt64} // TODO: is this defined?
{$DEFINE HAS_InterlockedCompareExchange_Pointers}
{$DEFINE HAS_SharedSuffix}
// size_t and psize_t are only available on Unix systems (FreeBSD, Linux, etc)
{$IFDEF UNIX}
  {$DEFINE HAS_SIZE_T}
  {$DEFINE HAS_PSIZE_T}
{$ENDIF}
{$DEFINE HAS_PtrInt}
{$DEFINE HAS_PtrUInt}
{$DEFINE HAS_LPGUID}
{$DEFINE HAS_PPAnsiChar}
{$IFDEF WINDOWS}
  {$DEFINE HAS_ULONG_PTR}
  {.$DEFINE HAS_ULONGLONG} // TODO: is this defined?
{$ENDIF}
{$DEFINE HAS_UNIT_ctypes}
{$IFNDEF FPUNONE}
  {$DEFINE HAS_TIMEUNITS} // TODO: when were they introduced?
{$ENDIF}
{$DEFINE HAS_TThread_NameThreadForDebugging}
{$DEFINE DEPRECATED_TThread_SuspendResume}
{$DEFINE HAS_NativeInt}
{$DEFINE HAS_NativeUInt}
{$DEFINE HAS_PInt8}
{$DEFINE HAS_PUInt8}
{$DEFINE HAS_PInt16}
{$DEFINE HAS_PUInt16}
{$DEFINE HAS_PInt32}
{$DEFINE HAS_PUInt32}
{$IF FPC_FULLVERSION >= 30101}
  {$DEFINE HAS_STATIC_TThread_ForceQueue} // requires rev 37359+
{$ENDIF}

{$IFDEF FPC_REQUIRES_PROPER_ALIGNMENT}
  {$DEFINE REQUIRES_PROPER_ALIGNMENT}
{$ENDIF}

//IMPORTANT!!!!
//
//In DCC, MACOS means OS X.  In FreePascal, MACOS means MacIntosh System OS Classic.
{$IFDEF MACOS}
  {$DEFINE MACOS_CLASSIC}
{$ENDIF}

{$DEFINE WIDGET_LCL}

{$IFDEF KYLIXCOMPAT}
  {$linklib c}
{$ENDIF}