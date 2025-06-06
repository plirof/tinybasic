/*
 *
 *	$Id: language.h,v 1.1 2024/02/25 04:43:16 stefan Exp stefan $ 
 *
 *	Stefan's IoT BASIC interpreter 
 *
 * 	See the licence file on 
 *	https://github.com/slviajero/tinybasic for copyright/left.
 *    (GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007)
 *
 *	Author: Stefan Lenz, sl001@serverfabrik.de
 *
 *	This is the language definition file. Edit this to set the language 
 * 	capabilities.
 * 
 * MEMSIZE was moved to hardware.h now as it is a hardware setting.
 * 
 */

/*
 *	DEBUG switches on compiled debug mode. Consider using runtime 
 * 		debug with SET 0,x before using this.
 */
#define DEBUG 0

/*
 * Interpreter feature sets, choose one of the predefines or undefine all predefines and set the 
 * features in custom settings
 *
 * BASICFULL: full language set, use this with flash >32kB - ESPs, MKRs, Mega2560, RP2040, UNO R4
 * BASICINTEGER: integer BASIC with full language, use this with flash >32kB
 * BASICSIMPLE: integer BASIC with reduced language set, 32kB capable - for UNOs with a lot of device drivers
 * BASICSIMPLEWITHFLOAT: a small floating point BASIC, 32kB capable, for UNOs - good for UNOs with the need of float
 * BASICTINYWITHFLOAT: a floating point tinybasic, if you have 32kB and need complex device drivers
 * BASICMINIMAL: minimal language, just Palo Alto plus Arduino I/O, works on 168 with 1kB RAM and 16kB flash
 * 
 * The board will try to find the best language model for it's size and capabilities. Relies on the 
 * information hardware.h produces. It set one of the language models: 
 * 
 * BASICFULL, BASICSIMPLE, BASICMINIMAL.
 * 
 * Setting NOLANGUAGEHEURISTICS and then one of the models below will override this 
 * selection.
 */
#define LANGUAGEHEURISTICS

#ifndef LANGUAGEHEURISTICS
#undef  BASICFULL
#undef	BASICINTEGER
#define	BASICSIMPLE
#undef	BASICMINIMAL
#undef  BASICPALOALTO
#undef	BASICSIMPLEWITHFLOAT
#undef	BASICTINYWITHFLOAT
#endif

/*
 * Custom settings undef all the the language sets above when you are using this. Not all language
 * features work in all combinations.
 * 
 * HASAPPLE1: Apple 1 BASIC compatibility. This is the base for all other features.
 *  In this version the interpreter has a heap, a string pool and one dimensional arrays.
 * HASARDUINOIO: Arduino I/O functions, including millis() timer.
 * HASFILEIO: file I/O functions, including open, close, read, write, remove, rename.
 * HASTONE: tone() and noTone() functions for sound output mapped to the PLAY command.
 * HASPULSE: pulseIn() function for measuring pulse lengths. Pulse output. Both mapped to the PULSE command.
 * HASSTEFANSEXT: Stefan's BASIC extensions, including ELSE, PUT, GET, advanced FOR loops, SQR and POW.
 * HASERRORMSG: error messages for syntax and runtime errors.
 * HASVT52: VT52 terminal emulation for text output -> moved to hardware.h
 * HASFLOAT: floating point support.
 * HASGRAPH: graphics support, including line, circle, rectangle, fill, color.
 * HASDARTMOUTH: Dartmouth BASIC compatibility: single line DEF FN, ON, READ, DATA.
 * HASDARKARTS: Dark Arts BASIC is MALLOC, FIND, CLR for individual variables and EVAL for self modifying code.
 * HASIOT: IoT functions, Wire access, Sensor functions, MQTT. Needs strings and heap. STR, VAL, INSTR are 
 *  part of this. MQTT support only on Arduino-
 * HASMULTIDIM: two dimensional arrays and one dimensional string arrays.
 * HASTIMER: timer functions, AFTER and EVERY for periodic execution of programs.
 * HASEVENTS: event handling, EVENT command. 
 * HASERRORHANDLING: error handling with ERROR GOTO.
 * HASSTRUCT: structured language elements, WHILE WEND, REPEAT UNTIL, SWITCH CASE. Multi line IF THEN ELSE 
 * 	with the DO DEND construct.
 * HASMSSTRINGS: MS Basic compatible strings, RIGHT$, LEFT$, MID$, ASC, CHR$, and string addition with +.
 * 	Compatibility to MS BASICs is limited as this BASIC has only inplace string operations-
 * HASMULTILINEFUNCTIONS: multi line functions, DEF FN, FEND.
 * HASEDITOR: line editor for the console.
 * HASTINYBASICINPUT: Tiny BASIC compatible input using the expression parser. Expressions and variables 
 * 	are valid number input with it. Default now but can have odd side effects.
 * HASLONGNAMES: long variable names, up to 16 characters. Name length is set by MAXNAME in basic.h and
 * 	can be any value <128 bytes. Names are still only uppercase and all names will be uppercased by lexer.
 * HASHELP: show the commands of the interpreter. Will be extended to a help system.
 * HASFULLINSTR: the full C64 style INSTR command. Without this flag INSTR only accepts
 *	a single character as argument. This is much faster and leaner on an Arduino. 
 * 	This macro is activated when HASMSSTRINGS is set. 
 * HASLOOPOPT: optimizes the FOR loops for speed. This is a trade off between speed and 
 *  memory. It is activated by default. Speeup is about 10% on a Mac. On platforms
 *  with low memory bandwidth it is much more.
 * HASNUMSYSTEM: constants can be hex, octal, binary or decimal. This is not activated by 
 *  default. Currently only implemented in VAL() and STR().
 * HASBITWISE: has bitwise operations >>, << and the function BIT -> removed and default now.
 * 
 * not explicitely shown up here is HASCAMERA which is only triggered by the language heuristic
 * and is part of the runtime and hardware code
 * 
 * If you want to set everything manually, set NOLANGUAGEHEURISTICS above
 */

#ifndef LANGUAGEHEURISTICS
#define HASAPPLE1
#define HASARDUINOIO
#define HASFILEIO
#define HASTONE
#define HASPULSE
#define HASSTEFANSEXT
#define HASERRORMSG
#define HASFLOAT
#define HASGRAPH
#define HASDARTMOUTH
#define HASDARKARTS
#define HASIOT
#define HASMULTIDIM
#define HASTIMER
#define HASEVENTS
#define HASERRORHANDLING
#define HASSTRUCT
#define HASMSSTRINGS
#define HASMULTILINEFUNCTIONS
#define HASEDITOR
#define HASTINYBASICINPUT
#define HASLONGNAMES 
#define HASHELP
#define HASFULLINSTR
#define HASLOOPOPT
#define HASNUMSYSTEM
#endif

/*
 *
 * Odd stuff - these things change the behaviour of BASIC in some aspects.
 * They can be used to make the interpreter compatible with other dialects.
 * 
 * 	POWERRIGHTTOLEFT: normally the ^ operator works from left to right 
 *		which means 2^3^2 = (2^3)^2 = 8^2 = 64. Setting this flag would 
 *		change the behaviour to 2^3^2 = 2^(3^2) = 512
 *  MSARRAYLIMITS: in BASIC arrays start at 1 and DIM A(10) creates 10 
 *      elements. With MSARRAYLIMITS defined, arrays start at 0 and have 
 *      n+1 elements. This can be changed at any time with SET 21,0 or 1.
 *  SUPPRESSSUBSTRINGS: switch off substring logic by default, makes only sense with 
 *      HASMSSTRINGS activated. With this, the syntax of strings and string 
 *      arrays is comaptible to MS strings (only used to preset the variable now).
 * 		SET 20 can change this at runtime. 
 *  USELONGJUMP: use the longjmp feature of C. This greatly simplifies 
 *      error handling at the cost of portability to some MCU platforms
 *      currently only experimental. It costs memory for the jump buffer. 
 *      Don't use it on very small systems. LONGJUMP must be set to 0 or 1 as 
 *      it is used in boolean expression in the code
 *  BOOLEANMODE: switch the behaviour of BASICs boolean operators. Default (-1)
 *      is to cast all numbers to signed 16bit and then do bitwise arithemtic.
 *      In this mode false is 0 and -1 is true. (1) is C style boolean arithemtic.
 *      In this mode true is 1 and false is 0. AND and OR still do bitwise operations
 *      but NOT is C not. SET 19,1 or -1 can change this at runtime.
 *  HAS64BIT: 64 bit floating point support on platforms that have a 64 bit double. 
 *      Counterexample: AVR 8bit does not have 64 bit floating point.
 * HAS32BITINT: 32 bit integer support on 8 bit platforms.
 * HASPOWER: the POWER operator ^ is available in addition to the POW function.
 * HASUSRCALL: the USR and CALL functions. On small systems they need a lot 
 *      of flash and can be disabled.
 */

#undef POWERRIGHTTOLEFT
#undef MSARRAYLIMITS
#undef SUPPRESSSUBSTRINGS
#define USELONGJUMP 0
#define BOOLEANMODE -1
#undef  HAS64BIT
#undef  HAS32BITINT
#define HASPOWER 
#define HASUSRCALL

/* Palo Alto plus Arduino functions */
#ifdef BASICMINIMAL
#undef HASAPPLE1
#define HASARDUINOIO
#undef HASFILEIO
#undef HASTONE
#undef HASPULSE
#undef HASSTEFANSEXT
#undef HASERRORMSG
#undef HASFLOAT
#undef HASGRAPH
#undef HASDARTMOUTH
#undef HASDARKARTS
#undef HASIOT
#undef HASMULTIDIM
#undef HASTIMER
#undef HASEVENTS
#undef HASERRORHANDLING
#undef HASSTRUCT
#undef HASMSSTRINGS
#undef HASMULTILINEFUNCTIONS
#undef HASEDITOR
#define HASTINYBASICINPUT
#undef HASLONGNAMES 
#undef HASHELP
#undef HASFULLINSTR
#undef HASLOOPOPT
#undef HASNUMSYSTEM
#undef HASPOWER
#undef HASUSRCALL
#endif

/* the original Palo Alto Tinybasic, this is the real minimum */
#ifdef BASICPALOALTO
#undef HASAPPLE1
#undef HASARDUINOIO
#undef HASFILEIO
#undef HASTONE
#undef HASPULSE
#undef HASSTEFANSEXT
#undef HASERRORMSG
#undef HASFLOAT
#undef HASGRAPH
#undef HASDARTMOUTH
#undef HASDARKARTS
#undef HASIOT
#undef HASMULTIDIM
#undef HASTIMER
#undef HASEVENTS
#undef HASERRORHANDLING
#undef HASSTRUCT
#undef HASMSSTRINGS
#undef HASMULTILINEFUNCTIONS
#undef HASEDITOR
#define HASTINYBASICINPUT
#undef HASLONGNAMES 
#undef HASHELP
#undef HASLOOPOPT
#undef HASNUMSYSTEM
#undef HASBITWISE
#undef HASFULLINSTR
#undef HASLOOPOPT
#undef HASNUMSYSTEM
#undef HASPOWER
#undef HASUSRCALL
#endif

/* all features minus float and tone */
#ifdef  BASICINTEGER
#define HASAPPLE1
#define HASARDUINOIO
#define HASFILEIO
#define HASTONE
#define HASPULSE
#define HASSTEFANSEXT
#define HASERRORMSG
#undef  HASFLOAT
#define HASGRAPH
#define HASDARTMOUTH
#define HASDARKARTS
#define HASIOT
#define HASMULTIDIM
#define HASTIMER
#define HASEVENTS
#define HASERRORHANDLING
#define HASSTRUCT
#define HASMSSTRINGS
#define HASMULTILINEFUNCTIONS
#define HASEDITOR
#define HASTINYBASICINPUT
#define HASLONGNAMES 
#define HASHELP
#define HASFULLINSTR
#define HASLOOPOPT
#define HASNUMSYSTEM
#endif

/* a simple integer basic for small systems mainly the UNO */
#ifdef  BASICSIMPLE
#define HASAPPLE1
#define HASARDUINOIO
#define HASFILEIO
#define HASTONE
#define HASPULSE
#define HASSTEFANSEXT
#define HASERRORMSG
#undef  HASFLOAT
#undef  HASGRAPH
#define HASDARTMOUTH
#undef  HASDARKARTS
#define HASIOT
#undef  HASMULTIDIM
#define HASTIMER
#define HASEVENTS
#define HASERRORHANDLING
#undef 	HASSTRUCT
#undef  HASMSSTRINGS
#undef HASMULTILINEFUNCTIONS
#undef HASEDITOR
#define HASTINYBASICINPUT
#undef HASLONGNAMES 
#undef HASHELP
#undef HASFULLINSTR
#undef HASLOOPOPT
#undef HASNUMSYSTEM
#undef HASPOWER
#undef HASUSRCALL
#endif

/* a small integer BASIC for 32kB systems with big cores */
#ifdef  BASICSMALL
#define HASAPPLE1
#define HASARDUINOIO
#undef  HASFILEIO
#undef  HASTONE
#undef  HASPULSE
#define HASSTEFANSEXT
#define HASERRORMSG
#undef  HASFLOAT
#undef  HASGRAPH
#undef  HASDARTMOUTH
#undef  HASDARKARTS
#define HASIOT
#undef  HASMULTIDIM
#define HASTIMER
#define HASEVENTS
#define HASERRORHANDLING
#undef  HASSTRUCT
#undef HASMSSTRINGS
#undef HASMULTILINEFUNCTIONS
#undef HASEDITOR
#define HASTINYBASICINPUT
#undef HASLONGNAMES 
#undef HASHELP
#undef HASFULLINSTR
#undef HASLOOPOPT
#undef HASNUMSYSTEM
#undef HASPOWER
#undef HASUSRCALL
#endif


/* all features activated */
#ifdef BASICFULL
#define HASAPPLE1
#define HASARDUINOIO
#define HASFILEIO
#define HASTONE
#define HASPULSE
#define HASSTEFANSEXT
#define HASERRORMSG
#define HASFLOAT
#define HASGRAPH
#define HASDARTMOUTH
#define HASDARKARTS
#define HASIOT
#define HASMULTIDIM
#define HASTIMER
#define HASEVENTS
#define HASERRORHANDLING
#define HASSTRUCT
#define HASMSSTRINGS
#define HASMULTILINEFUNCTIONS
#define HASEDITOR
#define HASTINYBASICINPUT
#define HASLONGNAMES 
#define HASHELP
#define HASFULLINSTR
#define HASLOOPOPT
#define HASNUMSYSTEM
#endif

/* a simple BASIC with float support */
#ifdef BASICSIMPLEWITHFLOAT
#define HASAPPLE1
#define HASARDUINOIO
#undef HASFILEIO
#undef HASTONE
#undef HASPULSE
#define HASSTEFANSEXT
#define HASERRORMSG
#define HASFLOAT
#undef HASGRAPH
#define HASDARTMOUTH
#undef HASDARKARTS
#undef HASIOT
#undef HASMULTIDIM
#undef HASTIMER
#undef HASEVENTS
#undef HASERRORHANDLING
#undef HASSTRUCT
#undef HASMSSTRINGS
#undef HASMULTILINEFUNCTIONS
#undef HASEDITOR
#define HASTINYBASICINPUT
#undef HASLONGNAMES 
#undef HASHELP
#undef HASFULLINSTR
#undef HASLOOPOPT
#undef HASNUMSYSTEM
#undef HASPOWER
#undef HASUSRCALL
#endif

/* a Tinybasic with float support */
#ifdef BASICTINYWITHFLOAT
#define HASAPPLE1
#define HASARDUINOIO
#undef HASFILEIO
#undef HASTONE
#undef HASPULSE
#define HASSTEFANSEXT
#define HASERRORMSG
#define HASFLOAT
#undef HASGRAPH
#undef HASDARTMOUTH
#undef HASDARKARTS
#undef HASIOT
#undef HASMULTIDIM
#undef HASTIMER
#undef HASEVENTS
#undef HASERRORHANDLING
#undef HASSTRUCT
#undef HASMSSTRINGS
#undef HASMULTILINEFUNCTIONS
#undef HASEDITOR
#define HASTINYBASICINPUT
#undef HASLONGNAMES 
#undef HASHELP
#undef HASFULLINSTR
#undef HASLOOPOPT
#undef HASNUMSYSTEM
#undef HASPOWER
#undef HASUSRCALL
#endif

/* 
 *	Language feature dependencies
 * 
 * Dartmouth and darkarts needs the heap which is in Apple 1
 * IoT needs strings and the heap, also Apple 1
 * 
 * String arrays need multi dimensional capabilities
 *
 * The structured language set needs ELSE from STEFANSEXT
 *
 */
#if defined(HASMULTILINEFUNCTIONS)
#define HASDARTMOUTH
#endif

#if defined(HASDARTMOUTH) || defined(HASDARKARTS) || defined(HASIOT) || defined(HASMSSTRINGS)
#define HASAPPLE1
#endif

#if defined(HASSTRUCT)
#define HASSTEFANSEXT
#endif

/* MS strings also bring the full INSTR */
#if defined(HASMSSTRINGS)
#define HASFULLINSTR
#endif

/* dependencies on the hardware */
#if !defined(DISPLAYHASGRAPH) 
#undef HASGRAPH
#endif

/* the camera sits in the long token space */
#if defined(HASCAMERA)
#define HASLONGTOKENS
#endif
