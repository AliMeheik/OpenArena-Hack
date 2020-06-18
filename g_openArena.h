
//THIS IS A MESS, DONT CARE ABOUT CLEANING THIS

#ifndef G_OPENARENA_H__
#define G_OPENARENA_H__
/*======================================================
 *
 *
 * idTech3 classes to be used in hack
 *
 * ====================================================*/
#ifndef __Q_SHARED_H
#define __Q_SHARED_H

// q_shared.h -- included first by ALL program modules.
// A user mod should never modify this file

//#ifdef STANDALONE
#define PRODUCT_NAME			"ioq3+oa"
#define BASEGAME			"baseoa"
#define CLIENT_WINDOW_TITLE     	"OpenArena"
#define CLIENT_WINDOW_MIN_TITLE 	"OA"
/*#else
#define PRODUCT_NAME			"ioq3"
#define BASEGAME			"baseq3"
#define CLIENT_WINDOW_TITLE     	"ioquake3"
#define CLIENT_WINDOW_MIN_TITLE 	"ioq3"
#endif*/

#ifdef _MSC_VER
#define PRODUCT_VERSION "1.35"
#endif

#define Q3_VERSION PRODUCT_NAME " " PRODUCT_VERSION

#define MAX_TEAMNAME 32

#ifdef _MSC_VER

#pragma warning(disable : 4018)     // signed/unsigned mismatch
#pragma warning(disable : 4032)
#pragma warning(disable : 4051)
#pragma warning(disable : 4057)		// slightly different base types
#pragma warning(disable : 4100)		// unreferenced formal parameter
#pragma warning(disable : 4115)
#pragma warning(disable : 4125)		// decimal digit terminates octal escape sequence
#pragma warning(disable : 4127)		// conditional expression is constant
#pragma warning(disable : 4136)
#pragma warning(disable : 4152)		// nonstandard extension, function/data pointer conversion in expression
//#pragma warning(disable : 4201)
//#pragma warning(disable : 4214)
#pragma warning(disable : 4244)
#pragma warning(disable : 4142)		// benign redefinition
//#pragma warning(disable : 4305)		// truncation from const double to float
//#pragma warning(disable : 4310)		// cast truncates constant value
//#pragma warning(disable:  4505) 	// unreferenced local function has been removed
#pragma warning(disable : 4514)
#pragma warning(disable : 4702)		// unreachable code
#pragma warning(disable : 4711)		// selected for automatic inline expansion
#pragma warning(disable : 4220)		// varargs matches remaining parameters
//#pragma intrinsic( memset, memcpy )
#endif

//Ignore __attribute__ on non-gcc platforms
#ifndef __GNUC__
#ifndef __attribute__
#define __attribute__(x)
#endif
#endif

#if (defined _MSC_VER)
#define Q_EXPORT __declspec(dllexport)
#elif (defined __SUNPRO_C)
#define Q_EXPORT __global
#elif ((__GNUC__ >= 3) && (!__EMX__) && (!sun))
#define Q_EXPORT __attribute__((visibility("default")))
#else
#define Q_EXPORT
#endif

// content masks
#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_BODY)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE)
/**********************************************************************
  VM Considerations

  The VM can not use the standard system headers because we aren't really
  using the compiler they were meant for.  We use bg_lib.h which contains
  prototypes for the functions we define for our own use in bg_lib.c.

  When writing mods, please add needed headers HERE, do not start including
  stuff like <stdio.h> in the various .c files that make up each of the VMs
  since you will be including system headers files can will have issues.

  Remember, if you use a C library function that is not defined in bg_lib.c,
  you will have to add your own version for support in the VM.

 **********************************************************************/

#ifdef Q3_VM

#include "../game/bg_lib.h"

typedef int intptr_t;

#else

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

// vsnprintf is ISO/IEC 9899:1999
// abstracting this to make it portable
#ifdef _WIN32
#define Q_vsnprintf _vsnprintf
#define Q_snprintf _snprintf
#else
#define Q_vsnprintf vsnprintf
#define Q_snprintf snprintf
#endif

#ifdef _MSC_VER
#include <io.h>

typedef __int64 int64_t;
typedef __int32 int32_t;
typedef __int16 int16_t;
typedef unsigned __int64 uint64_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;
#else
#include <stdint.h>
#endif

#endif


/*
   ===========================================================================
   Copyright (C) 1999-2005 Id Software, Inc.

   This file is part of Quake III Arena source code.

   Quake III Arena source code is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the License,
   or (at your option) any later version.

   Quake III Arena source code is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Quake III Arena source code; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
   ===========================================================================
   */

#ifndef __Q_PLATFORM_H
#define __Q_PLATFORM_H

// this is for determining if we have an asm version of a C function
#ifdef Q3_VM

#define id386 0
#define idppc 0
#define idppc_altivec 0

#else

#if (defined _M_IX86 || defined __i386__) && !defined(C_ONLY)
#define id386 1
#else
#define id386 0
#endif

#if (defined(powerc) || defined(powerpc) || defined(ppc) || \
        defined(__ppc) || defined(__ppc__)) && !defined(C_ONLY)
#define idppc 1
#if defined(__VEC__)
#define idppc_altivec 1
#ifdef MACOS_X  // Apple's GCC does this differently than the FSF.
#define VECCONST_UINT8(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
    (vector unsigned char) (a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p)
#else
#define VECCONST_UINT8(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) \
    (vector unsigned char) {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p}
#endif
#else
#define idppc_altivec 0
#endif
#else
#define idppc 0
#define idppc_altivec 0
#endif

#endif

#ifndef __ASM_I386__ // don't include the C bits if included from qasm.h

// for windows fastcall option
#define QDECL

//================================================================= WIN32 ===

#ifdef __MINGW32__

#undef QDECL
#define QDECL __cdecl

#if defined( _MSC_VER )
#define OS_STRING "win_msvc"
#elif defined __MINGW32__
#define OS_STRING "win_mingw"
#endif

#define ID_INLINE __inline
#define PATH_SEP '\\'

#if defined( _M_IX86 ) || defined( __i386__ )
#define ARCH_STRING "x86"
#elif defined _M_ALPHA
#define ARCH_STRING "AXP"
#endif

#define Q3_LITTLE_ENDIAN

#define DLL_EXT ".dll"

#endif

//KK-OAX, This is a little hack to be able to build dll's for debugging under Visual Studio
//Simple copy/paste/rename of the #ifdef __MINGW32__
#ifdef VSTUDIO

#undef QDECL
#define QDECL __cdecl

#if defined( _MSC_VER )
#define OS_STRING "win_msvc"
#elif defined __MINGW32__
#define OS_STRING "win_mingw"
#endif

#define ID_INLINE __inline
#define PATH_SEP '\\'

#if defined( _M_IX86 ) || defined( __i386__ )
#define ARCH_STRING "x86"
#elif defined _M_ALPHA
#define ARCH_STRING "AXP"
#endif

#define Q3_LITTLE_ENDIAN

#define DLL_EXT ".dll"

#endif
//============================================================== MAC OS X ===

#if defined(MACOS_X) || defined(__APPLE_CC__)

// make sure this is defined, just for sanity's sake...
#ifndef MACOS_X
#define MACOS_X
#endif

#define OS_STRING "macosx"
#define ID_INLINE inline
#define PATH_SEP '/'

#ifdef __ppc__
#define ARCH_STRING "ppc"
#define Q3_BIG_ENDIAN
#elif defined __i386__
#define ARCH_STRING "i386"
#define Q3_LITTLE_ENDIAN
#endif

#define DLL_EXT ".dylib"

#endif

//================================================================= LINUX ===

#ifdef __linux__

#include <endian.h>

#define OS_STRING "linux"
#define ID_INLINE inline
#define PATH_SEP '/'

#if defined __i386__
#define ARCH_STRING "i386"
#elif defined __x86_64__
#define ARCH_STRING "x86_64"
#elif defined __powerpc64__
#define ARCH_STRING "ppc64"
#elif defined __powerpc__
#define ARCH_STRING "ppc"
#elif defined __s390__
#define ARCH_STRING "s390"
#elif defined __s390x__
#define ARCH_STRING "s390x"
#elif defined __ia64__
#define ARCH_STRING "ia64"
#elif defined __alpha__
#define ARCH_STRING "alpha"
#elif defined __sparc__
#define ARCH_STRING "sparc"
#elif defined __arm__
#define ARCH_STRING "arm"
#elif defined __cris__
#define ARCH_STRING "cris"
#elif defined __hppa__
#define ARCH_STRING "hppa"
#elif defined __mips__
#define ARCH_STRING "mips"
#elif defined __sh__
#define ARCH_STRING "sh"
#endif

#if __FLOAT_WORD_ORDER == __BIG_ENDIAN
#define Q3_BIG_ENDIAN
#else
#define Q3_LITTLE_ENDIAN
#endif

#define DLL_EXT ".so"

#endif

//=================================================================== BSD ===

#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__)

#include <sys/types.h>
#include <machine/endian.h>

#ifndef __BSD__
#define __BSD__
#endif

#if defined(__FreeBSD__)
#define OS_STRING "freebsd"
#elif defined(__OpenBSD__)
#define OS_STRING "openbsd"
#elif defined(__NetBSD__)
#define OS_STRING "netbsd"
#endif

#define ID_INLINE inline
#define PATH_SEP '/'

#ifdef __i386__
#define ARCH_STRING "i386"
#elif defined __axp__
#define ARCH_STRING "alpha"
#endif

#if BYTE_ORDER == BIG_ENDIAN
#define Q3_BIG_ENDIAN
#else
#define Q3_LITTLE_ENDIAN
#endif

#define DLL_EXT ".so"

#endif

//================================================================= SUNOS ===

#ifdef __sun

#include <stdint.h>
#include <sys/byteorder.h>

#define OS_STRING "solaris"
#define ID_INLINE inline
#define PATH_SEP '/'

#ifdef __i386__
#define ARCH_STRING "i386"
#elif defined __sparc
#define ARCH_STRING "sparc"
#endif

#if defined( _BIG_ENDIAN )
#define Q3_BIG_ENDIAN
#elif defined( _LITTLE_ENDIAN )
#define Q3_LITTLE_ENDIAN
#endif

#define DLL_EXT ".so"

#endif

//================================================================== IRIX ===

#ifdef __sgi

#define OS_STRING "irix"
#define ID_INLINE __inline
#define PATH_SEP '/'

#define ARCH_STRING "mips"

#define Q3_BIG_ENDIAN // SGI's MIPS are always big endian

#define DLL_EXT ".so"

#endif

//================================================================== Q3VM ===

#ifdef Q3_VM

#define OS_STRING "q3vm"
#define ID_INLINE
#define PATH_SEP '/'

#define ARCH_STRING "bytecode"

#define DLL_EXT ".qvm"

#endif

//===========================================================================

//catch missing defines in above blocks



//endianness
short ShortSwap (short l);
int LongSwap (int l);
float FloatSwap (const float *f);

#if defined( Q3_BIG_ENDIAN ) && defined( Q3_LITTLE_ENDIAN )
#error "Endianness defined as both big and little"
#elif defined( Q3_BIG_ENDIAN )

#define LittleShort(x) ShortSwap(x)
#define LittleLong(x) LongSwap(x)
#define LittleFloat(x) FloatSwap(&x)
#define BigShort
#define BigLong
#define BigFloat

#elif defined( Q3_LITTLE_ENDIAN )

#define LittleShort
#define LittleLong
#define LittleFloat
#define BigShort(x) ShortSwap(x)
#define BigLong(x) LongSwap(x)
#define BigFloat(x) FloatSwap(&x)

#elif defined( Q3_VM )

#define LittleShort
#define LittleLong
#define LittleFloat
#define BigShort
#define BigLong
#define BigFloat



//platform string
#ifdef NDEBUG
#define PLATFORM_STRING OS_STRING "-" ARCH_STRING
#else
#define PLATFORM_STRING OS_STRING "-" ARCH_STRING "-debug"
#endif

#endif

#endif

//=============================================================

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];
extern vec3_t vec3_origin;
typedef unsigned char 		byte;

typedef enum {qfalse, qtrue}	qboolean;

typedef union {
    float f;
    int i;
    unsigned int ui;
} floatint_t;

typedef int		qhandle_t;
typedef int		sfxHandle_t;
typedef int		fileHandle_t;
typedef int		clipHandle_t;

#define PAD(x,y) (((x)+(y)-1) & ~((y)-1))

#ifdef __GNUC__
#define ALIGN(x) __attribute__((aligned(x)))
#else
#define ALIGN(x)
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define	MAX_QINT			0x7fffffff
#define	MIN_QINT			(-MAX_QINT-1)


// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

// the game guarantees that no string from the network will ever
// exceed MAX_STRING_CHARS
#define	MAX_STRING_CHARS	1024	// max length of a string passed to Cmd_TokenizeString
#define	MAX_STRING_TOKENS	1024	// max tokens resulting from Cmd_TokenizeString
#define	MAX_TOKEN_CHARS		1024	// max length of an individual token

#define	MAX_INFO_STRING		1024
#define	MAX_INFO_KEY		  1024
#define	MAX_INFO_VALUE		1024

#define	BIG_INFO_STRING		8192  // used for system info key only
#define	BIG_INFO_KEY		  8192
#define	BIG_INFO_VALUE		8192


#define	MAX_QPATH			64		// max length of a quake game pathname
#ifdef PATH_MAX
#define MAX_OSPATH			PATH_MAX
#else
#define	MAX_OSPATH			256		// max length of a filesystem pathname
#endif

#define	MAX_NAME_LENGTH		32		// max length of a client name

#define	MAX_SAY_TEXT	150

// paramters for command buffer stuffing
typedef enum {
    EXEC_NOW,			// don't return until completed, a VM should NEVER use this,
    // because some commands might cause the VM to be unloaded...
    EXEC_INSERT,		// insert at current position, but don't run yet
    EXEC_APPEND			// add to end of the command buffer (normal case)
} cbufExec_t;


//
// these aren't needed by any of the VMs.  put in another header?
//
#define	MAX_MAP_AREA_BYTES		32		// bit vector of area visibility


// print levels from renderer (FIXME: set up for game / cgame?)
typedef enum {
    PRINT_ALL,
    PRINT_DEVELOPER,		// only print when "developer 1"
    PRINT_WARNING,
    PRINT_ERROR
} printParm_t;

typedef enum {
    CG_PRINT,
    CG_ERROR,
    CG_MILLISECONDS,
    CG_CVAR_REGISTER,
    CG_CVAR_UPDATE,
    CG_CVAR_SET,
    CG_CVAR_VARIABLESTRINGBUFFER,
    CG_ARGC,
    CG_ARGV,
    CG_ARGS,
    CG_FS_FOPENFILE,
    CG_FS_READ,
    CG_FS_WRITE,
    CG_FS_FCLOSEFILE,
    CG_SENDCONSOLECOMMAND,
    CG_ADDCOMMAND,
    CG_SENDCLIENTCOMMAND,
    CG_UPDATESCREEN,
    CG_CM_LOADMAP,
    CG_CM_NUMINLINEMODELS,
    CG_CM_INLINEMODEL,
    CG_CM_LOADMODEL,
    CG_CM_TEMPBOXMODEL,
    CG_CM_POINTCONTENTS,
    CG_CM_TRANSFORMEDPOINTCONTENTS,
    CG_CM_BOXTRACE,
    CG_CM_TRANSFORMEDBOXTRACE,
    CG_CM_MARKFRAGMENTS,
    CG_S_STARTSOUND,
    CG_S_STARTLOCALSOUND,
    CG_S_CLEARLOOPINGSOUNDS,
    CG_S_ADDLOOPINGSOUND,
    CG_S_UPDATEENTITYPOSITION,
    CG_S_RESPATIALIZE,
    CG_S_REGISTERSOUND,
    CG_S_STARTBACKGROUNDTRACK,
    CG_R_LOADWORLDMAP,
    CG_R_REGISTERMODEL,
    CG_R_REGISTERSKIN,
    CG_R_REGISTERSHADER,
    CG_R_CLEARSCENE,
    CG_R_ADDREFENTITYTOSCENE,
    CG_R_ADDPOLYTOSCENE,
    CG_R_ADDLIGHTTOSCENE,
    CG_R_RENDERSCENE,
    CG_R_SETCOLOR,
    CG_R_DRAWSTRETCHPIC,
    CG_R_MODELBOUNDS,
    CG_R_LERPTAG,
    CG_GETGLCONFIG,
    CG_GETGAMESTATE,
    CG_GETCURRENTSNAPSHOTNUMBER,
    CG_GETSNAPSHOT,
    CG_GETSERVERCOMMAND,
    CG_GETCURRENTCMDNUMBER,
    CG_GETUSERCMD,
    CG_SETUSERCMDVALUE,
    CG_R_REGISTERSHADERNOMIP,
    CG_MEMORY_REMAINING,
    CG_R_REGISTERFONT,
    CG_KEY_ISDOWN,
    CG_KEY_GETCATCHER,
    CG_KEY_SETCATCHER,
    CG_KEY_GETKEY,
    CG_PC_ADD_GLOBAL_DEFINE,
    CG_PC_LOAD_SOURCE,
    CG_PC_FREE_SOURCE,
    CG_PC_READ_TOKEN,
    CG_PC_SOURCE_FILE_AND_LINE,
    CG_S_STOPBACKGROUNDTRACK,
    CG_REAL_TIME,
    CG_SNAPVECTOR,
    CG_REMOVECOMMAND,
    CG_R_LIGHTFORPOINT,
    CG_CIN_PLAYCINEMATIC,
    CG_CIN_STOPCINEMATIC,
    CG_CIN_RUNCINEMATIC,
    CG_CIN_DRAWCINEMATIC,
    CG_CIN_SETEXTENTS,
    CG_R_REMAP_SHADER,
    CG_S_ADDREALLOOPINGSOUND,
    CG_S_STOPLOOPINGSOUND,

    CG_CM_TEMPCAPSULEMODEL,
    CG_CM_CAPSULETRACE,
    CG_CM_TRANSFORMEDCAPSULETRACE,
    CG_R_ADDADDITIVELIGHTTOSCENE,
    CG_GET_ENTITY_TOKEN,
    CG_R_ADDPOLYSTOSCENE,
    CG_R_INPVS,
    // 1.32
    CG_FS_SEEK,

    /*
       CG_LOADCAMERA,
       CG_STARTCAMERA,
       CG_GETCAMERAINFO,
       */

    CG_MEMSET = 100,
    CG_MEMCPY,
    CG_STRNCPY,
    CG_SIN,
    CG_COS,
    CG_ATAN2,
    CG_SQRT,
    CG_FLOOR,
    CG_CEIL,
    CG_TESTPRINTINT,
    CG_TESTPRINTFLOAT,
    CG_ACOS
} cgameImport_t;

#ifdef ERR_FATAL
#undef ERR_FATAL			// this is be defined in malloc.h
#endif

// parameters to the main Error routine
typedef enum {
    ERR_FATAL,					// exit the entire game with a popup window
    ERR_DROP,					// print to console and disconnect from game
    ERR_SERVERDISCONNECT,		// don't kill server
    ERR_DISCONNECT,				// client disconnected from the server
    ERR_NEED_CD					// pop up the need-cd dialog
} errorParm_t;


// font rendering values used by ui and cgame

#define PROP_GAP_WIDTH			3
#define PROP_SPACE_WIDTH		8
#define PROP_HEIGHT				27
#define PROP_SMALL_SIZE_SCALE	0.75

#define BLINK_DIVISOR			200
#define PULSE_DIVISOR			75

#define UI_LEFT			0x00000000	// default
#define UI_CENTER		0x00000001
#define UI_RIGHT		0x00000002
#define UI_FORMATMASK	0x00000007
#define UI_SMALLFONT	0x00000010
#define UI_BIGFONT		0x00000020	// default
#define UI_GIANTFONT	0x00000040
#define UI_DROPSHADOW	0x00000800
#define UI_BLINK		0x00001000
#define UI_INVERSE		0x00002000
#define UI_PULSE		0x00004000

#if defined(_DEBUG) && !defined(BSPC)
#define HUNK_DEBUG
#endif

typedef enum {
    h_high,
    h_low,
    h_dontcare
} ha_pref;

#ifdef HUNK_DEBUG
#define Hunk_Alloc( size, preference )				Hunk_AllocDebug(size, preference, #size, __FILE__, __LINE__)
void *Hunk_AllocDebug( int size, ha_pref preference, char *label, char *file, int line );
#else
void *Hunk_Alloc( int size, ha_pref preference );
#endif

#define Com_Memset memset
#define Com_Memcpy memcpy

#define CIN_system	1
#define CIN_loop	2
#define	CIN_hold	4
#define CIN_silent	8
#define CIN_shader	16

/*
   ==============================================================

   MATHLIB

   ==============================================================
   */


typedef float vec_t;
typedef vec_t vec2_t[2];
//typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];

typedef	int	fixed4_t;
typedef	int	fixed8_t;
typedef	int	fixed16_t;

#ifndef M_PI
#define M_PI		3.14159265358979323846f	// matches value in gcc v2 math.h
#endif

#define NUMVERTEXNORMALS	162
extern	vec3_t	bytedirs[NUMVERTEXNORMALS];

// all drawing is done to a 640*480 virtual screen size
// and will be automatically scaled to the real resolution
#define	SCREEN_WIDTH		640
#define	SCREEN_HEIGHT		480

#define TINYCHAR_WIDTH		(SMALLCHAR_WIDTH)
#define TINYCHAR_HEIGHT		(SMALLCHAR_HEIGHT/2)

#define SMALLCHAR_WIDTH		8
#define SMALLCHAR_HEIGHT	16

#define BIGCHAR_WIDTH		16
#define BIGCHAR_HEIGHT		16

#define	GIANTCHAR_WIDTH		32
#define	GIANTCHAR_HEIGHT	48

extern	vec4_t		colorBlack;
extern	vec4_t		colorRed;
extern	vec4_t		colorGreen;
extern	vec4_t		colorBlue;
extern	vec4_t		colorYellow;
extern	vec4_t		colorMagenta;
extern	vec4_t		colorCyan;
extern	vec4_t		colorWhite;
extern	vec4_t		colorLtGrey;
extern	vec4_t		colorMdGrey;
extern	vec4_t		colorDkGrey;

#define Q_COLOR_ESCAPE	'^'
#define Q_IsColorString(p)      ((p) && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) >= '0' && *((p)+1) <= '8') // ^[0-8]
#define COLOR_BLACK		'0'
#define COLOR_RED		'1'
#define COLOR_GREEN		'2'
#define COLOR_YELLOW	'3'
#define COLOR_BLUE		'4'
#define COLOR_CYAN		'5'
#define COLOR_MAGENTA	'6'
#define COLOR_WHITE		'7'
#define ColorIndex(c)   ((c) - '0')

#define S_COLOR_BLACK	"^0"
#define S_COLOR_RED		"^1"
#define S_COLOR_GREEN	"^2"
#define S_COLOR_YELLOW	"^3"
#define S_COLOR_BLUE	"^4"
#define S_COLOR_CYAN	"^5"
#define S_COLOR_MAGENTA	"^6"
#define S_COLOR_WHITE	"^7"
#define S_COLOR_MENU	"^8"

extern vec4_t	g_color_table[9];

#define	MAKERGB( v, r, g, b ) v[0]=r;v[1]=g;v[2]=b
#define	MAKERGBA( v, r, g, b, a ) v[0]=r;v[1]=g;v[2]=b;v[3]=a

#define DEG2RAD( a ) ( ( (a) * M_PI ) / 180.0F )
#define RAD2DEG( a ) ( ( (a) * 180.0f ) / M_PI )

struct cplane_s;

extern	vec3_t	axisDefault[3];

#define	nanmask (255<<23)

#define	IS_NAN(x) (((*(int *)&x)&nanmask)==nanmask)

#if idppc

static ID_INLINE float Q_rsqrt( float number ) {
    float x = 0.5f * number;
    float y;
#ifdef __GNUC__            
    asm("frsqrte %0,%1" : "=f" (y) : "f" (number));
#else
    y = __frsqrte( number );
#endif
    return y * (1.5f - (x * y * y));
}

#ifdef __GNUC__            
static ID_INLINE float Q_fabs(float x) {
    float abs_x;

    asm("fabs %0,%1" : "=f" (abs_x) : "f" (x));
    return abs_x;
}
#else
#define Q_fabs __fabsf
#endif

#else
float Q_fabs( float f );
float Q_rsqrt( float f );		// reciprocal square root
#endif

#define SQRTFAST( x ) ( (x) * Q_rsqrt( x ) )

signed char ClampChar( int i );
signed short ClampShort( int i );

// this isn't a real cheap function to call!
int DirToByte( vec3_t dir );
void ByteToDir( int b, vec3_t dir );

#if	1

#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))

#else

#define DotProduct(x,y)			_DotProduct(x,y)
#define VectorSubtract(a,b,c)	_VectorSubtract(a,b,c)
#define VectorAdd(a,b,c)		_VectorAdd(a,b,c)
#define VectorCopy(a,b)			_VectorCopy(a,b)
#define	VectorScale(v, s, o)	_VectorScale(v,s,o)
#define	VectorMA(v, s, b, o)	_VectorMA(v,s,b,o)

#endif

#ifdef Q3_VM
#ifdef VectorCopy
#undef VectorCopy
// this is a little hack to get more efficient copies in our interpreter
typedef struct {
    float	v[3];
} vec3struct_t;
#define VectorCopy(a,b)	(*(vec3struct_t *)b=*(vec3struct_t *)a)
#endif
#endif

#define VectorClear(a)			((a)[0]=(a)[1]=(a)[2]=0)
#define VectorNegate(a,b)		((b)[0]=-(a)[0],(b)[1]=-(a)[1],(b)[2]=-(a)[2])
#define VectorSet(v, x, y, z)	((v)[0]=(x), (v)[1]=(y), (v)[2]=(z))
#define Vector4Copy(a,b)		((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2],(b)[3]=(a)[3])

#define	SnapVector(v) {v[0]=((int)(v[0]));v[1]=((int)(v[1]));v[2]=((int)(v[2]));}
// just in case you do't want to use the macros
vec_t _DotProduct( const vec3_t v1, const vec3_t v2 );
void _VectorSubtract( const vec3_t veca, const vec3_t vecb, vec3_t out );
void _VectorAdd( const vec3_t veca, const vec3_t vecb, vec3_t out );
void _VectorCopy( const vec3_t in, vec3_t out );
void _VectorScale( const vec3_t in, float scale, vec3_t out );
void _VectorMA( const vec3_t veca, float scale, const vec3_t vecb, vec3_t vecc );

unsigned ColorBytes3 (float r, float g, float b);
unsigned ColorBytes4 (float r, float g, float b, float a);

float NormalizeColor( const vec3_t in, vec3_t out );

float RadiusFromBounds( const vec3_t mins, const vec3_t maxs );
void ClearBounds( vec3_t mins, vec3_t maxs );
void AddPointToBounds( const vec3_t v, vec3_t mins, vec3_t maxs );


// fast vector normalize routine that does not check to make sure
// that length != 0, nor does it return length, uses rsqrt approximation

#else
int VectorCompare( const vec3_t v1, const vec3_t v2 );

vec_t VectorLength( const vec3_t v );

vec_t VectorLengthSquared( const vec3_t v );

vec_t Distance( const vec3_t p1, const vec3_t p2 );

vec_t DistanceSquared( const vec3_t p1, const vec3_t p2 );

void VectorNormalizeFast( vec3_t v );

void VectorInverse( vec3_t v );

void CrossProduct( const vec3_t v1, const vec3_t v2, vec3_t cross );

#endif

vec_t VectorNormalize (vec3_t v);		// returns vector length
vec_t VectorNormalize2( const vec3_t v, vec3_t out );
void Vector4Scale( const vec4_t in, vec_t scale, vec4_t out );
void VectorRotate( vec3_t in, vec3_t matrix[3], vec3_t out );
int Q_log2(int val);

float Q_acos(float c);

int		Q_rand( int *seed );
float	Q_random( int *seed );
float	Q_crandom( int *seed );

#define random()	((rand () & 0x7fff) / ((float)0x7fff))
#define crandom()	(2.0 * (random() - 0.5))

void vectoangles( const vec3_t value1, vec3_t angles);
void AnglesToAxis( const vec3_t angles, vec3_t axis[3] );

void AxisClear( vec3_t axis[3] );
void AxisCopy( vec3_t in[3], vec3_t out[3] );

void SetPlaneSignbits( struct cplane_s *out );
int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct cplane_s *plane);

qboolean BoundsIntersect(const vec3_t mins, const vec3_t maxs,
        const vec3_t mins2, const vec3_t maxs2);
qboolean BoundsIntersectSphere(const vec3_t mins, const vec3_t maxs,
        const vec3_t origin, vec_t radius);
qboolean BoundsIntersectPoint(const vec3_t mins, const vec3_t maxs,
        const vec3_t origin);

float	AngleMod(float a);
float	LerpAngle (float from, float to, float frac);
float	AngleSubtract( float a1, float a2 );
void	AnglesSubtract( vec3_t v1, vec3_t v2, vec3_t v3 );

float AngleNormalize360 ( float angle );
float AngleNormalize180 ( float angle );
float AngleDelta ( float angle1, float angle2 );

qboolean PlaneFromPoints( vec4_t plane, const vec3_t a, const vec3_t b, const vec3_t c );
void ProjectPointOnPlane( vec3_t dst, const vec3_t p, const vec3_t normal );
void RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point, float degrees );
void RotateAroundDirection( vec3_t axis[3], float yaw );
void MakeNormalVectors( const vec3_t forward, vec3_t right, vec3_t up );
// perpendicular vector could be replaced by this

//int	PlaneTypeForNormal (vec3_t normal);

void MatrixMultiply(float in1[3][3], float in2[3][3], float out[3][3]);
void AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
void PerpendicularVector( vec3_t dst, const vec3_t src );
int Q_isnan( float x );


//=============================================

float Com_Clamp( float min, float max, float value );

char	*COM_SkipPath( char *pathname );
const char	*COM_GetExtension( const char *name );
void	COM_StripExtension(const char *in, char *out, int destsize);
void	COM_DefaultExtension( char *path, int maxSize, const char *extension );

void	COM_BeginParseSession( const char *name );
int		COM_GetCurrentParseLine( void );
char	*COM_Parse( char **data_p );
char	*COM_ParseExt( char **data_p, qboolean allowLineBreak );
int		COM_Compress( char *data_p );
void	COM_ParseError( char *format, ... ) __attribute__ ((format (printf, 1, 2)));
void	COM_ParseWarning( char *format, ... ) __attribute__ ((format (printf, 1, 2)));
//int		COM_ParseInfos( char *buf, int max, char infos[][MAX_INFO_STRING] );

#define MAX_TOKENLENGTH		1024

#ifndef TT_STRING
//token types
#define TT_STRING					1			// string
#define TT_LITERAL					2			// literal
#define TT_NUMBER					3			// number
#define TT_NAME						4			// name
#define TT_PUNCTUATION				5			// punctuation
#endif

typedef struct pc_token_s
{
    int type;
    int subtype;
    int intvalue;
    float floatvalue;
    char string[MAX_TOKENLENGTH];
} pc_token_t;

// data is an in/out parm, returns a parsed out token

void	COM_MatchToken( char**buf_p, char *match );

void SkipBracedSection (char **program);
void SkipRestOfLine ( char **data );

void Parse1DMatrix (char **buf_p, int x, float *m);
void Parse2DMatrix (char **buf_p, int y, int x, float *m);
void Parse3DMatrix (char **buf_p, int z, int y, int x, float *m);

void	QDECL Com_sprintf (char *dest, int size, const char *fmt, ...) __attribute__ ((format (printf, 3, 4)));

char *Com_SkipTokens( char *s, int numTokens, char *sep );
char *Com_SkipCharset( char *s, char *sep );

void Com_RandomBytes( byte *string, int len );

// mode parm for FS_FOpenFile
typedef enum {
    FS_READ,
    FS_WRITE,
    FS_APPEND,
    FS_APPEND_SYNC
} fsMode_t;

typedef enum {
    FS_SEEK_CUR,
    FS_SEEK_END,
    FS_SEEK_SET
} fsOrigin_t;

//=============================================

int Q_isprint( int c );
int Q_islower( int c );
int Q_isupper( int c );
int Q_isalpha( int c );

// portable case insensitive compare
int		Q_stricmp (const char *s1, const char *s2);
#define Q_strequal(s1,s2) (Q_stricmp(s1,s2)==0)
int		Q_strncmp (const char *s1, const char *s2, int n);
int		Q_stricmpn (const char *s1, const char *s2, int n);
char	*Q_strlwr( char *s1 );
char	*Q_strupr( char *s1 );
const char	*Q_stristr( const char *s, const char *find);

// buffer size safe library replacements
/**
 * Copies a string from one array to another in a safe way
 *
 * @param dest (out) pointer to destination array
 * @param src (in) pointer to source array
 * @param destsize size of the destination array, at most destsize-1 will be copied
 */
void	Q_strncpyz( char *dest, const char *src, int destsize );
/**
 * Appends a string to another string. The function protects against overflow.
 * The size is the max size of the destination AFTER the string has been appended
 * If the length of dest is larger or equal to destsize then nothing will be appended.
 *
 * @param dest (in/out) pointer to the string that will be appended to
 * @param size size of the destination array
 * @param src (in) the string to append
 */
void	Q_strcat( char *dest, int size, const char *src );

/**
 * strlen that counts the length of the string after the color sequences have
 * been removed. Example: "A^2I" = 2 because it will be printed "AI"
 *
 * @param string the string to
 * @return the length of the string as printed
 */
int Q_PrintStrlen( const char *string );
/**
 * Removes all colors from a string.
 *
 * @param string (in/out) the string to make color less
 * @return pointer to the string
 */
char *Q_CleanStr( char *string );
// Count the number of char tocount encountered in string
int Q_CountChar(const char *string, char tocount);

//=============================================

// 64-bit integers for global rankings interface
// implemented as a struct for qvm compatibility
typedef struct
{
    byte	b0;
    byte	b1;
    byte	b2;
    byte	b3;
    byte	b4;
    byte	b5;
    byte	b6;
    byte	b7;
} qint64;

//=============================================
/*
   short	BigShort(short l);
   short	LittleShort(short l);
   int		BigLong (int l);
   int		LittleLong (int l);
   qint64  BigLong64 (qint64 l);
   qint64  LittleLong64 (qint64 l);
   float	BigFloat (const float *l);
   float	LittleFloat (const float *l);

   void	Swap_Init (void);
   */
char	* QDECL va(char *format, ...) __attribute__ ((format (printf, 1, 2)));

#define TRUNCATE_LENGTH	64
void Com_TruncateLongString( char *buffer, const char *s );

//=============================================

//
// key / value info strings
//
char *Info_ValueForKey( const char *s, const char *key );
void Info_RemoveKey( char *s, const char *key );
void Info_RemoveKey_big( char *s, const char *key );
void Info_SetValueForKey( char *s, const char *key, const char *value );
void Info_SetValueForKey_Big( char *s, const char *key, const char *value );
qboolean Info_Validate( const char *s );
void Info_NextPair( const char **s, char *key, char *value );

// this is only here so the functions in q_shared.c and bg_*.c can link
void	QDECL Com_Error( int level, const char *error, ... ) __attribute__ ((format (printf, 2, 3))) __attribute__((noreturn));
void	QDECL Com_Printf( const char *msg, ... ) __attribute__ ((format (printf, 1, 2)));


/*
   ==========================================================

   CVARS (console variables)

   Many variables can be used for cheating purposes, so when
   cheats is zero, force all unspecified variables to their
   default values.
   ==========================================================
   */

#define	CVAR_ARCHIVE		1	// set to cause it to be saved to vars.rc
// used for system variables, not for player
// specific configurations
#define	CVAR_USERINFO		2	// sent to server on connect or change
#define	CVAR_SERVERINFO		4	// sent in response to front end requests
#define	CVAR_SYSTEMINFO		8	// these cvars will be duplicated on all clients
#define	CVAR_INIT			16	// don't allow change from console at all,
// but can be set from the command line
#define	CVAR_LATCH			32	// will only change when C code next does
// a Cvar_Get(), so it can't be changed
// without proper initialization.  modified
// will be set, even though the value hasn't
// changed yet
#define	CVAR_ROM			64	// display only, cannot be set by user at all
#define	CVAR_USER_CREATED	128	// created by a set command
#define	CVAR_TEMP			256	// can be set even when cheats are disabled, but is not archived
#define CVAR_CHEAT			512	// can not be changed if cheats are disabled
#define CVAR_NORESTART		1024	// do not clear when a cvar_restart is issued

#define CVAR_SERVER_CREATED	2048	// cvar was created by a server the client connected to.
#define CVAR_NONEXISTENT	0xFFFFFFFF	// Cvar doesn't exist.

// nothing outside the Cvar_*() functions should modify these fields!
typedef struct cvar_s {
    char		*name;
    char		*string;
    char		*resetString;		// cvar_restart will reset to this value
    char		*latchedString;		// for CVAR_LATCH vars
    int			flags;
    qboolean	modified;			// set each time the cvar is changed
    int			modificationCount;	// incremented each time the cvar is changed
    float		value;				// atof( string )
    int			integer;			// atoi( string )
    struct cvar_s *next;
    struct cvar_s *hashNext;
} cvar_t;

#define	MAX_CVAR_VALUE_STRING	256

typedef int	cvarHandle_t;

// the modules that run in the virtual machine can't access the cvar_t directly,
// so they must ask for structured updates
typedef struct {
    cvarHandle_t	handle;
    int			modificationCount;
    float		value;
    int			integer;
    char		string[MAX_CVAR_VALUE_STRING];
} vmCvar_t;

/*
   ==============================================================

   COLLISION DETECTION

   ==============================================================
   */
/*
   ===========================================================================
   Copyright (C) 1999-2005 Id Software, Inc.

   This file is part of Quake III Arena source code.

   Quake III Arena source code is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the License,
   or (at your option) any later version.

   Quake III Arena source code is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Quake III Arena source code; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
   ===========================================================================
   */
//
// This file must be identical in the quake and utils directories

// contents flags are seperate bits
// a given brush can contribute multiple content bits

// these definitions also need to be in q_shared.h!

#define	CONTENTS_SOLID			1		// an eye is never valid in a solid
#define	CONTENTS_LAVA			8
#define	CONTENTS_SLIME			16
#define	CONTENTS_WATER			32
#define	CONTENTS_FOG			64

#define CONTENTS_NOTTEAM1		0x0080
#define CONTENTS_NOTTEAM2		0x0100
#define CONTENTS_NOBOTCLIP		0x0200

#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000
//bot specific contents types
#define	CONTENTS_TELEPORTER		0x40000
#define	CONTENTS_JUMPPAD		0x80000
#define CONTENTS_CLUSTERPORTAL	0x100000
#define CONTENTS_DONOTENTER		0x200000
#define CONTENTS_BOTCLIP		0x400000
#define CONTENTS_MOVER			0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_BODY			0x2000000	// should never be on a brush, only in game
#define	CONTENTS_CORPSE			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes not used for the bsp
#define	CONTENTS_STRUCTURAL		0x10000000	// brushes used for the bsp
#define	CONTENTS_TRANSLUCENT	0x20000000	// don't consume surface fragments inside
#define	CONTENTS_TRIGGER		0x40000000
#define	CONTENTS_NODROP			0x80000000	// don't leave bodies or items (death fog, lava)

#define	SURF_NODAMAGE			0x1		// never give falling damage
#define	SURF_SLICK				0x2		// effects game physics
#define	SURF_SKY				0x4		// lighting from environment map
#define	SURF_LADDER				0x8
#define	SURF_NOIMPACT			0x10	// don't make missile explosions
#define	SURF_NOMARKS			0x20	// don't leave missile marks
#define	SURF_FLESH				0x40	// make flesh sounds and effects
#define	SURF_NODRAW				0x80	// don't generate a drawsurface at all
#define	SURF_HINT				0x100	// make a primary bsp splitter
#define	SURF_SKIP				0x200	// completely ignore, allowing non-closed brushes
#define	SURF_NOLIGHTMAP			0x400	// surface doesn't need a lightmap
#define	SURF_POINTLIGHT			0x800	// generate lighting info at vertexes
#define	SURF_METALSTEPS			0x1000	// clanking footsteps
#define	SURF_NOSTEPS			0x2000	// no footstep sounds
#define	SURF_NONSOLID			0x4000	// don't collide against curves with this set
#define	SURF_LIGHTFILTER		0x8000	// act as a light filter during q3map -light
#define	SURF_ALPHASHADOW		0x10000	// do per-pixel light shadow casting in q3map
#define	SURF_NODLIGHT			0x20000	// don't dlight even if solid (solid lava, skies)
#define SURF_DUST				0x40000 // leave a dust trail when walking on this surface


// plane types are used to speed some tests
// 0-2 are axial planes
#define	PLANE_X			0
#define	PLANE_Y			1
#define	PLANE_Z			2
#define	PLANE_NON_AXIAL	3


/*
   =================
   PlaneTypeForNormal
   =================
   */

#define PlaneTypeForNormal(x) (x[0] == 1.0 ? PLANE_X : (x[1] == 1.0 ? PLANE_Y : (x[2] == 1.0 ? PLANE_Z : PLANE_NON_AXIAL) ) )

// plane_t structure
// !!! if this is changed, it must be changed in asm code too !!!
typedef struct cplane_s {
    vec3_t	normal;
    float	dist;
    byte	type;			// for fast side tests: 0,1,2 = axial, 3 = nonaxial
    byte	signbits;		// signx + (signy<<1) + (signz<<2), used as lookup during collision
    byte	pad[2];
} cplane_t;


// a trace is returned when a box is swept through the world
typedef struct {
    qboolean	allsolid;	// if true, plane is not valid
    qboolean	startsolid;	// if true, the initial point was in a solid area
    float		fraction;	// time completed, 1.0 = didn't hit anything
    vec3_t		endpos;		// final position
    cplane_t	plane;		// surface normal at impact, transformed to world space
    int			surfaceFlags;	// surface hit
    int			contents;	// contents on other side of surface hit
    int			entityNum;	// entity the contacted sirface is a part of
} trace_t;

// trace->entityNum can also be 0 to (MAX_GENTITIES-1)
// or ENTITYNUM_NONE, ENTITYNUM_WORLD


// markfragments are returned by CM_MarkFragments()
typedef struct {
    int		firstPoint;
    int		numPoints;
} markFragment_t;



typedef struct {
    vec3_t		origin;
    vec3_t		axis[3];
} orientation_t;

//=====================================================================


// in order from highest priority to lowest
// if none of the catchers are active, bound key strings will be executed
#define KEYCATCH_CONSOLE		0x0001
#define	KEYCATCH_UI					0x0002
#define	KEYCATCH_MESSAGE		0x0004
#define	KEYCATCH_CGAME			0x0008


// sound channels
// channel 0 never willingly overrides
// other channels will allways override a playing sound on that channel
typedef enum {
    CHAN_AUTO,
    CHAN_LOCAL,		// menu sounds, etc
    CHAN_WEAPON,
    CHAN_VOICE,
    CHAN_ITEM,
    CHAN_BODY,
    CHAN_LOCAL_SOUND,	// chat messages, etc
    CHAN_ANNOUNCER		// announcer voices, etc
} soundChannel_t;


/*
   ========================================================================

   ELEMENTS COMMUNICATED ACROSS THE NET

   ========================================================================
   */

#define	ANGLE2SHORT(x)	((int)((x)*65536/360) & 65535)
#define	SHORT2ANGLE(x)	((x)*(360.0/65536))

#define	SNAPFLAG_RATE_DELAYED	1
#define	SNAPFLAG_NOT_ACTIVE		2	// snapshot used during connection and for zombies
#define SNAPFLAG_SERVERCOUNT	4	// toggled every map_restart so transitions can be detected

//
// per-level limits
//
#define	MAX_CLIENTS			64		// absolute limit
#define MAX_LOCATIONS		64

#define	GENTITYNUM_BITS		10		// don't need to send any more
#define	MAX_GENTITIES		(1<<GENTITYNUM_BITS)

// entitynums are communicated with GENTITY_BITS, so any reserved
// values that are going to be communcated over the net need to
// also be in this range
#define	ENTITYNUM_NONE		(MAX_GENTITIES-1)
#define	ENTITYNUM_WORLD		(MAX_GENTITIES-2)
#define	ENTITYNUM_MAX_NORMAL	(MAX_GENTITIES-2)


#define	MAX_MODELS			256		// these are sent over the net as 8 bits
#define	MAX_SOUNDS			256		// so they cannot be blindly increased


#define	MAX_CONFIGSTRINGS	1024

// these are the only configstrings that the system reserves, all the
// other ones are strictly for servergame to clientgame communication
#define	CS_SERVERINFO		0		// an info string with all the serverinfo cvars
#define	CS_SYSTEMINFO		1		// an info string for server system to client system configuration (timescale, etc)

#define	RESERVED_CONFIGSTRINGS	2	// game can't modify below this, only the system can

#define	MAX_GAMESTATE_CHARS	16000
typedef struct {
    int			stringOffsets[MAX_CONFIGSTRINGS];
    char		stringData[MAX_GAMESTATE_CHARS];
    int			dataCount;
} gameState_t;

//=========================================================

// bit field limits
#define	MAX_STATS				16
#define	MAX_PERSISTANT			16
#define	MAX_POWERUPS			16
#define	MAX_WEAPONS				16		

#define	MAX_PS_EVENTS			2

#define PS_PMOVEFRAMECOUNTBITS	6

// playerState_t is the information needed by both the client and server
// to predict player motion and actions
// nothing outside of pmove should modify these, or some degree of prediction error
// will occur

// you can't add anything to this without modifying the code in msg.c

// playerState_t is a full superset of entityState_t as it is used by players,
// so if a playerState_t is transmitted, the entityState_t can be fully derived
// from it.
typedef struct playerState_s {
    int			commandTime;	// cmd->serverTime of last executed command
    int			pm_type;
    int			bobCycle;		// for view bobbing and footstep generation
    int			pm_flags;		// ducked, jump_held, etc
    int			pm_time;

    vec3_t		origin;
    vec3_t		velocity;
    int			weaponTime;
    int			gravity;
    int			speed;
    int			delta_angles[3];	// add to command angles to get view direction
    // changed by spawns, rotating objects, and teleporters

    int			groundEntityNum;// ENTITYNUM_NONE = in air

    int			legsTimer;		// don't change low priority animations until this runs out
    int			legsAnim;		// mask off ANIM_TOGGLEBIT

    int			torsoTimer;		// don't change low priority animations until this runs out
    int			torsoAnim;		// mask off ANIM_TOGGLEBIT

    int			movementDir;	// a number 0 to 7 that represents the reletive angle
    // of movement to the view angle (axial and diagonals)
    // when at rest, the value will remain unchanged
    // used to twist the legs during strafing

    vec3_t		grapplePoint;	// location of grapple to pull towards if PMF_GRAPPLE_PULL

    int			eFlags;			// copied to entityState_t->eFlags

    int			eventSequence;	// pmove generated events
    int			events[MAX_PS_EVENTS];
    int			eventParms[MAX_PS_EVENTS];

    int			externalEvent;	// events set on player from another source
    int			externalEventParm;
    int			externalEventTime;

    int			clientNum;		// ranges from 0 to MAX_CLIENTS-1
    int			weapon;			// copied to entityState_t->weapon
    int			weaponstate;

    vec3_t		viewangles;		// for fixed views
    int			viewheight;

    // damage feedback
    int			damageEvent;	// when it changes, latch the other parms
    int			damageYaw;
    int			damagePitch;
    int			damageCount;

    int			stats[MAX_STATS];
    int			persistant[MAX_PERSISTANT];	// stats that aren't cleared on death
    int			powerups[MAX_POWERUPS];	// level.time that the powerup runs out
    int			ammo[MAX_WEAPONS];

    int			generic1;
    int			loopSound;
    int			jumppad_ent;	// jumppad entity hit this frame

    // not communicated over the net at all
    int			ping;			// server to game info for scoreboard
    int			pmove_framecount;	// FIXME: don't transmit over the network
    int			jumppad_frame;
    int			entityEventSequence;
} playerState_t;


//====================================================================


//
// usercmd_t->button bits, many of which are generated by the client system,
// so they aren't game/cgame only definitions
//
#define	BUTTON_ATTACK		1
#define	BUTTON_TALK			2			// displays talk balloon and disables actions
#define	BUTTON_USE_HOLDABLE	4
#define	BUTTON_GESTURE		8
#define	BUTTON_WALKING		16			// walking can't just be infered from MOVE_RUN
// because a key pressed late in the frame will
// only generate a small move value for that frame
// walking will use different animations and
// won't generate footsteps
#define BUTTON_AFFIRMATIVE	32
#define	BUTTON_NEGATIVE		64

#define BUTTON_GETFLAG		128
#define BUTTON_GUARDBASE	256
#define BUTTON_PATROL		512
#define BUTTON_FOLLOWME		1024

#define	BUTTON_ANY			2048			// any key whatsoever

#define	MOVE_RUN			120			// if forwardmove or rightmove are >= MOVE_RUN,
// then BUTTON_WALKING should be set

// usercmd_t is sent to the server each client frame
typedef struct usercmd_s {
    int				serverTime;
    int				angles[3];
    int 			buttons;
    byte			weapon;           // weapon 
    signed char	forwardmove, rightmove, upmove;
} usercmd_t;

//===================================================================

// if entityState->solid == SOLID_BMODEL, modelindex is an inline model number
#define	SOLID_BMODEL	0xffffff

typedef enum {
    TR_STATIONARY,
    TR_INTERPOLATE,				// non-parametric, but interpolate between snapshots
    TR_LINEAR,
    TR_LINEAR_STOP,
    TR_SINE,					// value = base + sin( time / duration ) * delta
    TR_GRAVITY
} trType_t;

typedef struct {
    trType_t	trType;
    int		trTime;
    int		trDuration;			// if non 0, trTime + trDuration = stop time
    vec3_t	trBase;
    vec3_t	trDelta;			// velocity, etc
} trajectory_t;

// entityState_t is the information conveyed from the server
// in an update message about entities that the client will
// need to render in some way
// Different eTypes may use the information in different ways
// The messages are delta compressed, so it doesn't really matter if
// the structure size is fairly large

typedef struct entityState_s {
    int		number;			// entity index
    int		eType;			// entityType_t
    int		eFlags;

    trajectory_t	pos;	// for calculating position
    trajectory_t	apos;	// for calculating angles

    int		time;
    int		time2;

    vec3_t	origin;
    vec3_t	origin2;

    vec3_t	angles;
    vec3_t	angles2;

    int		otherEntityNum;	// shotgun sources, etc
    int		otherEntityNum2;

    int		groundEntityNum;	// -1 = in air

    int		constantLight;	// r + (g<<8) + (b<<16) + (intensity<<24)
    int		loopSound;		// constantly loop this sound

    int		modelindex;
    int		modelindex2;
    int		clientNum;		// 0 to (MAX_CLIENTS - 1), for players and corpses
    int		frame;

    int		solid;			// for client side prediction, trap_linkentity sets this properly

    int		event;			// impulse events -- muzzle flashes, footsteps, etc
    int		eventParm;

    // for players
    int		powerups;		// bit flags
    int		weapon;			// determines weapon and flash model, etc
    int		legsAnim;		// mask off ANIM_TOGGLEBIT
    int		torsoAnim;		// mask off ANIM_TOGGLEBIT

    int		generic1;
} entityState_t;

typedef enum {
    CA_UNINITIALIZED,
    CA_DISCONNECTED, 	// not talking to a server
    CA_AUTHORIZING,		// not used any more, was checking cd key 
    CA_CONNECTING,		// sending request packets to the server
    CA_CHALLENGING,		// sending challenge packets to the server
    CA_CONNECTED,		// netchan_t established, getting gamestate
    CA_LOADING,			// only during cgame initialization, never during main loop
    CA_PRIMED,			// got gamestate, waiting for first frame
    CA_ACTIVE,			// game views should be displayed
    CA_CINEMATIC		// playing a cinematic or a static pic, not connected to a server
} connstate_t;

// font support 

#define GLYPH_START 0
#define GLYPH_END 255
#define GLYPH_CHARSTART 32
#define GLYPH_CHAREND 127
#define GLYPHS_PER_FONT GLYPH_END - GLYPH_START + 1
typedef struct {
    int height;       // number of scan lines
    int top;          // top of glyph in buffer
    int bottom;       // bottom of glyph in buffer
    int pitch;        // width for copying
    int xSkip;        // x adjustment
    int imageWidth;   // width of actual image
    int imageHeight;  // height of actual image
    float s;          // x offset in image where glyph starts
    float t;          // y offset in image where glyph starts
    float s2;
    float t2;
    qhandle_t glyph;  // handle to the shader with the glyph
    char shaderName[32];
} glyphInfo_t;

typedef struct {
    glyphInfo_t glyphs [GLYPHS_PER_FONT];
    float glyphScale;
    char name[MAX_QPATH];
} fontInfo_t;

#define Square(x) ((x)*(x))

// real time
//=============================================


typedef struct qtime_s {
    int tm_sec;     /* seconds after the minute - [0,59] */
    int tm_min;     /* minutes after the hour - [0,59] */
    int tm_hour;    /* hours since midnight - [0,23] */
    int tm_mday;    /* day of the month - [1,31] */
    int tm_mon;     /* months since January - [0,11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday - [0,6] */
    int tm_yday;    /* days since January 1 - [0,365] */
    int tm_isdst;   /* daylight savings time flag */
} qtime_t;


// server browser sources
// TTimo: AS_MPLAYER is no longer used
#define AS_LOCAL			0
#define AS_MPLAYER		1
#define AS_GLOBAL			2
#define AS_FAVORITES	3


// cinematic states
typedef enum {
    FMV_IDLE,
    FMV_PLAY,		// play
    FMV_EOF,		// all other conditions, i.e. stop/EOF/abort
    FMV_ID_BLT,
    FMV_ID_IDLE,
    FMV_LOOPED,
    FMV_ID_WAIT
} e_status;

typedef enum _flag_status {
    FLAG_ATBASE = 0,
    FLAG_TAKEN,			// CTF
    FLAG_TAKEN_RED,		// One Flag CTF
    FLAG_TAKEN_BLUE,	// One Flag CTF
    FLAG_DROPPED
} flagStatus_t;



#define	MAX_GLOBAL_SERVERS				4096
#define	MAX_OTHER_SERVERS					128
#define MAX_PINGREQUESTS					32
#define MAX_SERVERSTATUSREQUESTS	16

#define SAY_ALL		0
#define SAY_TEAM	1
#define SAY_TELL	2

#define CDKEY_LEN 16
#define CDCHKSUM_LEN 2


#endif	// __Q_SHARED_H













/*
   ===========================================================================
   Copyright (C) 1999-2005 Id Software, Inc.

   This file is part of Quake III Arena source code.

   Quake III Arena source code is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the License,
   or (at your option) any later version.

   Quake III Arena source code is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Quake III Arena source code; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
   ===========================================================================
   */
//
#ifndef __TR_TYPES_H
#define __TR_TYPES_H


#define	MAX_DLIGHTS		32		// can't be increased, because bit flags are used on surfaces
#define	MAX_ENTITIES		1023		// can't be increased without changing drawsurf bit packing

// renderfx flags
#define	RF_MINLIGHT		0x0001		// allways have some light (viewmodel, some items)
#define	RF_THIRD_PERSON		0x0002		// don't draw through eyes, only mirrors (player bodies, chat sprites)
#define	RF_FIRST_PERSON		0x0004		// only draw through eyes (view weapon, damage blood blob)
#define	RF_DEPTHHACK		0x0008		// for view weapon Z crunching

#define RF_CROSSHAIR		0x0010		// This item is a cross hair and will draw over everything similar to
// DEPTHHACK in stereo rendering mode, with the difference that the
// projection matrix won't be hacked to reduce the stereo separation as
// is done for the gun.

#define	RF_NOSHADOW		0x0040		// don't add stencil shadows

#define RF_LIGHTING_ORIGIN	0x0080		// use refEntity->lightingOrigin instead of refEntity->origin
// for lighting.  This allows entities to sink into the floor
// with their origin going solid, and allows all parts of a
// player to get the same lighting

#define	RF_SHADOW_PLANE		0x0100		// use refEntity->shadowPlane
#define	RF_WRAP_FRAMES		0x0200		// mod the model frames by the maxframes to allow continuous

// refdef flags
#define RDF_NOWORLDMODEL	0x0001		// used for player configuration screen
#define RDF_HYPERSPACE		0x0004		// teleportation effect

typedef struct {
    vec3_t		xyz;
    float		st[2];
    byte		modulate[4];
} polyVert_t;

typedef struct poly_s {
    qhandle_t			hShader;
    int					numVerts;
    polyVert_t			*verts;
} poly_t;

typedef enum {
    RT_MODEL,
    RT_POLY,
    RT_SPRITE,
    RT_BEAM,
    RT_RAIL_CORE,
    RT_RAIL_RINGS,
    RT_LIGHTNING,
    RT_PORTALSURFACE,		// doesn't draw anything, just info for portals

    RT_MAX_REF_ENTITY_TYPE
} refEntityType_t;

typedef struct model_s {
	char		name[MAX_QPATH];
	int 	    type;
	int			index;		// model = tr.models[model->index]

	int			dataSize;	// just for listing purposes
	int	        *bmodel;		// only if type == MOD_BRUSH
	int	        *mdv[8];	// only if type == MOD_MESH
	void	    *modelData;			// only if type == (MOD_MDR | MOD_IQM)

	int			 numLods;
} model_t;

typedef struct {
    refEntityType_t	reType;
    int			renderfx;

    qhandle_t	hModel;				// opaque type outside refresh

    // most recent data
    vec3_t		lightingOrigin;		// so multi-part models can be lit identically (RF_LIGHTING_ORIGIN)
    float		shadowPlane;		// projection shadows go here, stencils go slightly lower

    vec3_t		axis[3];			// rotation vectors
    qboolean	nonNormalizedAxes;	// axis are not normalized, i.e. they have scale
    float		origin[3];			// also used as MODEL_BEAM's "from"
    int			frame;				// also used as MODEL_BEAM's diameter

    // previous data for frame interpolation
    float		oldorigin[3];		// also used as MODEL_BEAM's "to"
    int			oldframe;
    float		backlerp;			// 0.0 = current, 1.0 = old

    // texturing
    int			skinNum;			// inline skin index
    qhandle_t	customSkin;			// NULL for default skin
    qhandle_t	customShader;		// use one image for the entire thing

    // misc
    byte		shaderRGBA[4];		// colors used by rgbgen entity shaders
    float		shaderTexCoord[2];	// texture coordinates used by tcMod entity modifiers
    float		shaderTime;			// subtracted from refdef time to control effect start times

    // extra sprite information
    float		radius;
    float		rotation;
} refEntity_t;


#define	MAX_RENDER_STRINGS			8
#define	MAX_RENDER_STRING_LENGTH	32

typedef struct {
    int			x, y, width, height;
    float		fov_x, fov_y;
    vec3_t		vieworg;
    vec3_t		viewaxis[3];		// transformation matrix

    // time in milliseconds for shader effects and other time dependent rendering issues
    int			time;

    int			rdflags;			// RDF_NOWORLDMODEL, etc

    // 1 bits will prevent the associated area from rendering at all
    byte		areamask[MAX_MAP_AREA_BYTES];

    // text messages for deform text shaders
    char		text[MAX_RENDER_STRINGS][MAX_RENDER_STRING_LENGTH];
} refdef_t;


typedef enum {
    STEREO_CENTER,
    STEREO_LEFT,
    STEREO_RIGHT
} stereoFrame_t;


/*
 ** glconfig_t
 **
 ** Contains variables specific to the OpenGL configuration
 ** being run right now.  These are constant once the OpenGL
 ** subsystem is initialized.
 */
typedef enum {
    TC_NONE,
    TC_S3TC,  // this is for the GL_S3_s3tc extension.
    TC_S3TC_ARB  // this is for the GL_EXT_texture_compression_s3tc extension.
} textureCompression_t;

typedef enum {
    GLDRV_ICD,					// driver is integrated with window system
    // WARNING: there are tests that check for
    // > GLDRV_ICD for minidriverness, so this
    // should always be the lowest value in this
    // enum set
    GLDRV_STANDALONE,			// driver is a non-3Dfx standalone driver
    GLDRV_VOODOO				// driver is a 3Dfx standalone driver
} glDriverType_t;

typedef enum {
    GLHW_GENERIC,			// where everthing works the way it should
    GLHW_3DFX_2D3D,			// Voodoo Banshee or Voodoo3, relevant since if this is
    // the hardware type then there can NOT exist a secondary
    // display adapter
    GLHW_RIVA128,			// where you can't interpolate alpha
    GLHW_RAGEPRO,			// where you can't modulate alpha on alpha textures
    GLHW_PERMEDIA2			// where you don't have src*dst
} glHardwareType_t;

typedef struct {
    char					renderer_string[MAX_STRING_CHARS];
    char					vendor_string[MAX_STRING_CHARS];
    char					version_string[MAX_STRING_CHARS];
    char					extensions_string[BIG_INFO_STRING];

    int						maxTextureSize;			// queried from GL
    int						numTextureUnits;		// multitexture ability

    int						colorBits, depthBits, stencilBits;

    glDriverType_t			driverType;
    glHardwareType_t		hardwareType;

    qboolean				deviceSupportsGamma;
    textureCompression_t	textureCompression;
    qboolean				textureEnvAddAvailable;

    int						vidWidth, vidHeight;
    // aspect is the screen's physical width / height, which may be different
    // than scrWidth / scrHeight if the pixels are non-square
    // normal screens should be 4/3, but wide aspect monitors may be 16/9
    float					windowAspect;

    int						displayFrequency;

    // synonymous with "does rendering consume the entire screen?", therefore
    // a Voodoo or Voodoo2 will have this set to TRUE, as will a Win32 ICD that
    // used CDS.
    qboolean				isFullscreen;
    qboolean				stereoEnabled;
    qboolean				smpActive;		// dual processor
} glconfig_t;

#endif	// __TR_TYPES_H

/*
   ===========================================================================
   Copyright (C) 1999-2005 Id Software, Inc.

   This file is part of Quake III Arena source code.

   Quake III Arena source code is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the License,
   or (at your option) any later version.

   Quake III Arena source code is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Quake III Arena source code; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
   ===========================================================================
   */
//
// bg_public.h -- definitions shared by both the server game and client game modules

// because games can change separately from the main system version, we need a
// second version that must match between game and cgame

#if defined(BG_PUBLIC_H)
#else
#define BG_PUBLIC_H 1

#define	GAME_VERSION		BASEGAME "-1"

#define	DEFAULT_GRAVITY		800
#define	GIB_HEALTH			-40
#define	ARMOR_PROTECTION	0.66

#define	MAX_ITEMS			256

#define	RANK_TIED_FLAG		0x4000

#define DEFAULT_SHOTGUN_SPREAD	700
#define DEFAULT_SHOTGUN_COUNT	11

#define	ITEM_RADIUS			15		// item sizes are needed for client side pickup detection

#define	LIGHTNING_RANGE		768

#define	SCORE_NOT_PRESENT	-9999	// for the CS_SCORES[12] when only one player is present

#define	VOTE_TIME			30000	// 30 seconds before vote times out

#define	MINS_Z				-24
#define	DEFAULT_VIEWHEIGHT	26
#define CROUCH_VIEWHEIGHT	12
#define	DEAD_VIEWHEIGHT		-16

//Domination points
#define MAX_DOMINATION_POINTS 6
#define MAX_DOMINATION_POINTS_NAMES 20

//
// config strings are a general means of communicating variable length strings
// from the server to all connected clients.
//

// CS_SERVERINFO and CS_SYSTEMINFO are defined in q_shared.h
#define	CS_MUSIC				2
#define	CS_MESSAGE				3		// from the map worldspawn's message field
#define	CS_MOTD					4		// g_motd string for server message of the day
#define	CS_WARMUP				5		// server time when the match will be restarted
#define	CS_SCORES1				6
#define	CS_SCORES2				7
#define CS_VOTE_TIME			8
#define CS_VOTE_STRING			9
#define	CS_VOTE_YES				10
#define	CS_VOTE_NO				11

#define CS_TEAMVOTE_TIME		12
#define CS_TEAMVOTE_STRING		14
#define	CS_TEAMVOTE_YES			16
#define	CS_TEAMVOTE_NO			18

#define	CS_GAME_VERSION			20
#define	CS_LEVEL_START_TIME		21		// so the timer only shows the current level
#define	CS_INTERMISSION			22		// when 1, fraglimit/timelimit has been hit and intermission will start in a second or two
#define CS_FLAGSTATUS			23		// string indicating flag status in CTF
#define CS_SHADERSTATE			24
#define CS_BOTINFO				25

#define	CS_ITEMS				27		// string of 0's and 1's that tell which items are present

#define	CS_MODELS				32
#define	CS_SOUNDS				(CS_MODELS+MAX_MODELS)
#define	CS_PLAYERS				(CS_SOUNDS+MAX_SOUNDS)
#define CS_LOCATIONS			(CS_PLAYERS+MAX_CLIENTS)
#define CS_PARTICLES			(CS_LOCATIONS+MAX_LOCATIONS)

#define CS_MAX				(CS_PARTICLES+MAX_LOCATIONS)

#if (CS_MAX) > MAX_CONFIGSTRINGS
#error overflow: (CS_MAX) > MAX_CONFIGSTRINGS
#endif

typedef enum {
    GT_FFA,				// free for all
    GT_TOURNAMENT,		// one on one tournament
    GT_SINGLE_PLAYER,	// single player ffa

    //-- team games go after this --

    GT_TEAM,			// team deathmatch

    //-- team games that uses bases go after this

    GT_CTF,				// capture the flag	
    GT_1FCTF,
    GT_OBELISK,
    GT_HARVESTER,	

    //-- custom game types, there will be a variable in 

    GT_ELIMINATION,			// team elimination (custom)
    GT_CTF_ELIMINATION,		// ctf elimination
    GT_LMS,				// Last man standing
    GT_DOUBLE_D,			// Double Domination
    GT_DOMINATION,			// Standard domination 12
    GT_MAX_GAME_TYPE

} gametype_t;

typedef enum { GENDER_MALE, GENDER_FEMALE, GENDER_NEUTER } gender_t;

/*
   ===================================================================================

   PMOVE MODULE

   The pmove code takes a player_state_t and a usercmd_t and generates a new player_state_t
   and some other output data.  Used for local prediction on the client game and true
   movement on the server game.
   ===================================================================================
   */

typedef enum {
    PM_NORMAL,		// can accelerate and turn
    PM_NOCLIP,		// noclip movement
    PM_SPECTATOR,	// still run into walls
    PM_DEAD,		// no acceleration or turning, but free falling
    PM_FREEZE,		// stuck in place with no control
    PM_INTERMISSION,	// no movement or status bar
    PM_SPINTERMISSION	// no movement or status bar
} pmtype_t;

typedef enum {
    WEAPON_READY, 
    WEAPON_RAISING,
    WEAPON_DROPPING,
    WEAPON_FIRING
} weaponstate_t;

// pmove->pm_flags
#define	PMF_DUCKED			1
#define	PMF_JUMP_HELD		2
#define	PMF_BACKWARDS_JUMP	8		// go into backwards land
#define	PMF_BACKWARDS_RUN	16		// coast down to backwards run
#define	PMF_TIME_LAND		32		// pm_time is time before rejump
#define	PMF_TIME_KNOCKBACK	64		// pm_time is an air-accelerate only time
#define	PMF_TIME_WATERJUMP	256		// pm_time is waterjump
#define	PMF_RESPAWNED		512		// clear after attack and jump buttons come up
#define	PMF_USE_ITEM_HELD	1024
#define PMF_GRAPPLE_PULL	2048	// pull towards grapple location
#define PMF_FOLLOW			4096	// spectate following another player
#define PMF_SCOREBOARD		8192	// spectate as a scoreboard
#define PMF_INVULEXPAND		16384	// invulnerability sphere set to full size
//Elimination players cannot fire in warmup
#define PMF_ELIMWARMUP		32768	//I hope this is more than 16 signed bits! (it's not but it just works anyway...)
//Don't add anymore, I have already set the sign bit :-(

#define	PMF_ALL_TIMES	(PMF_TIME_WATERJUMP|PMF_TIME_LAND|PMF_TIME_KNOCKBACK)

#define	MAXTOUCH	32
typedef struct {
    // state (in / out)
    playerState_t	*ps;

    // command (in)
    usercmd_t	cmd;
    int			tracemask;			// collide against these types of surfaces
    int			debugLevel;			// if set, diagnostic output will be printed
    qboolean	noFootsteps;		// if the game is setup for no footsteps by the server
    qboolean	gauntletHit;		// true if a gauntlet attack would actually hit something

    int			framecount;

    // results (out)
    int			numtouch;
    int			touchents[MAXTOUCH];

    vec3_t		mins, maxs;			// bounding box size

    int			watertype;
    int			waterlevel;

    float		xyspeed;

    // for fixed msec Pmove
    int			pmove_fixed;
    int			pmove_msec;

    //Sago's pmove
    int                     pmove_float;

    //Flags effecting movement (see dmflags)
    int                     pmove_flags;

    // callbacks to test the world
    // these will be different functions during game and cgame
    void		(*trace)( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask );
    int			(*pointcontents)( const vec3_t point, int passEntityNum );
} pmove_t;

// if a full pmove isn't done on the client, you can just update the angles
void PM_UpdateViewAngles( playerState_t *ps, const usercmd_t *cmd );
void Pmove (pmove_t *pmove);

//===================================================================================


// player_state->stats[] indexes
// NOTE: may not have more than 16
typedef enum {
    STAT_HEALTH,
    STAT_HOLDABLE_ITEM,
    STAT_PERSISTANT_POWERUP,
    STAT_WEAPONS,					// 16 bit fields
    STAT_ARMOR,				
    STAT_DEAD_YAW,					// look this direction when dead (FIXME: get rid of?)
    STAT_CLIENTS_READY,				// bit mask of clients wishing to exit the intermission (FIXME: configstring?)
    STAT_MAX_HEALTH					// health / armor limit, changable by handicap
} statIndex_t;


// player_state->persistant[] indexes
// these fields are the only part of player_state that isn't
// cleared on respawn
// NOTE: may not have more than 16
typedef enum {
    PERS_SCORE,						// !!! MUST NOT CHANGE, SERVER AND GAME BOTH REFERENCE !!!
    PERS_HITS,						// total points damage inflicted so damage beeps can sound on change
    PERS_RANK,						// player rank or team rank
    PERS_TEAM,						// player team
    PERS_SPAWN_COUNT,				// incremented every respawn
    PERS_PLAYEREVENTS,				// 16 bits that can be flipped for events
    PERS_ATTACKER,					// clientnum of last damage inflicter
    PERS_ATTACKEE_ARMOR,			// health/armor of last person we attacked
    PERS_KILLED,					// count of the number of times you died
    // player awards tracking
    PERS_IMPRESSIVE_COUNT,			// two railgun hits in a row
    PERS_EXCELLENT_COUNT,			// two successive kills in a short amount of time
    PERS_DEFEND_COUNT,				// defend awards
    PERS_ASSIST_COUNT,				// assist awards
    PERS_GAUNTLET_FRAG_COUNT,		// kills with the guantlet
    PERS_CAPTURES					// captures
} persEnum_t;


// entityState_t->eFlags
#define	EF_DEAD				0x00000001		// don't draw a foe marker over players with EF_DEAD
#define EF_TICKING			0x00000002		// used to make players play the prox mine ticking sound
#define	EF_TELEPORT_BIT		0x00000004		// toggled every time the origin abruptly changes
#define	EF_AWARD_EXCELLENT	0x00000008		// draw an excellent sprite
#define EF_PLAYER_EVENT		0x00000010
#define	EF_BOUNCE			0x00000010		// for missiles
#define	EF_BOUNCE_HALF		0x00000020		// for missiles
#define	EF_AWARD_GAUNTLET	0x00000040		// draw a gauntlet sprite
#define	EF_NODRAW			0x00000080		// may have an event, but no model (unspawned items)
#define	EF_FIRING			0x00000100		// for lightning gun
#define	EF_KAMIKAZE			0x00000200
#define	EF_MOVER_STOP		0x00000400		// will push otherwise
#define EF_AWARD_CAP		0x00000800		// draw the capture sprite
#define	EF_TALK				0x00001000		// draw a talk balloon
#define	EF_CONNECTION		0x00002000		// draw a connection trouble sprite
#define	EF_VOTED			0x00004000		// already cast a vote
#define	EF_AWARD_IMPRESSIVE	0x00008000		// draw an impressive sprite
#define	EF_AWARD_DEFEND		0x00010000		// draw a defend sprite
#define	EF_AWARD_ASSIST		0x00020000		// draw a assist sprite
#define EF_AWARD_DENIED		0x00040000		// denied
#define EF_TEAMVOTED		0x00080000		// already cast a team vote

// NOTE: may not have more than 16
typedef enum {
    PW_NONE,

    PW_QUAD,
    PW_BATTLESUIT,
    PW_HASTE,
    PW_INVIS,
    PW_REGEN,
    PW_FLIGHT,

    PW_REDFLAG,
    PW_BLUEFLAG,
    PW_NEUTRALFLAG,

    PW_SCOUT,
    PW_GUARD,
    PW_DOUBLER,
    PW_AMMOREGEN,
    PW_INVULNERABILITY,

    PW_NUM_POWERUPS

} powerup_t;

typedef enum {
    HI_NONE,

    HI_TELEPORTER,
    HI_MEDKIT,
    HI_KAMIKAZE,
    HI_PORTAL,
    HI_INVULNERABILITY,

    HI_NUM_HOLDABLE
} holdable_t;

typedef enum {
    DD_NONE,

    DD_POINTARED,
    DD_POINTABLUE,
    DD_POINTAWHITE,
    DD_POINTBRED,
    DD_POINTBBLUE,
    DD_POINTBWHITE
} doubled_t;

typedef enum {
    DOM_NONE,

    DOM_POINTRED,
    DOM_POINTBLUE,
    DOM_POINTWHITE,
} domination_t;


typedef enum {
    WP_NONE,

    WP_GAUNTLET,
    WP_MACHINEGUN,
    WP_SHOTGUN,
    WP_GRENADE_LAUNCHER,
    WP_ROCKET_LAUNCHER,
    WP_LIGHTNING,
    WP_RAILGUN,
    WP_PLASMAGUN,
    WP_BFG,
    WP_GRAPPLING_HOOK,
    WP_NAILGUN,
    WP_PROX_LAUNCHER,
    WP_CHAINGUN,

    WP_NUM_WEAPONS
} weapon_t;


// reward sounds (stored in ps->persistant[PERS_PLAYEREVENTS])
#define	PLAYEREVENT_DENIEDREWARD		0x0001
#define	PLAYEREVENT_GAUNTLETREWARD		0x0002
#define PLAYEREVENT_HOLYSHIT			0x0004

// entityState_t->event values
// entity events are for effects that take place reletive
// to an existing entities origin.  Very network efficient.

// two bits at the top of the entityState->event field
// will be incremented with each change in the event so
// that an identical event started twice in a row can
// be distinguished.  And off the value with ~EV_EVENT_BITS
// to retrieve the actual event number
#define	EV_EVENT_BIT1		0x00000100
#define	EV_EVENT_BIT2		0x00000200
#define	EV_EVENT_BITS		(EV_EVENT_BIT1|EV_EVENT_BIT2)

#define	EVENT_VALID_MSEC	300

typedef enum {
    EV_NONE,

    EV_FOOTSTEP,
    EV_FOOTSTEP_METAL,
    EV_FOOTSPLASH,
    EV_FOOTWADE,
    EV_SWIM,

    EV_STEP_4,
    EV_STEP_8,
    EV_STEP_12,
    EV_STEP_16,

    EV_FALL_SHORT,
    EV_FALL_MEDIUM,
    EV_FALL_FAR,

    EV_JUMP_PAD,			// boing sound at origin, jump sound on player

    EV_JUMP,                        //Event 14
    EV_WATER_TOUCH,	// foot touches
    EV_WATER_LEAVE,	// foot leaves
    EV_WATER_UNDER,	// head touches
    EV_WATER_CLEAR,	// head leaves

    EV_ITEM_PICKUP,			// normal item pickups are predictable
    EV_GLOBAL_ITEM_PICKUP,	// powerup / team sounds are broadcast to everyone

    EV_NOAMMO,
    EV_CHANGE_WEAPON,
    EV_FIRE_WEAPON,

    EV_USE_ITEM0,                   //Event 24
    EV_USE_ITEM1,
    EV_USE_ITEM2,
    EV_USE_ITEM3,
    EV_USE_ITEM4,
    EV_USE_ITEM5,
    EV_USE_ITEM6,
    EV_USE_ITEM7,
    EV_USE_ITEM8,
    EV_USE_ITEM9,
    EV_USE_ITEM10,
    EV_USE_ITEM11,
    EV_USE_ITEM12,
    EV_USE_ITEM13,
    EV_USE_ITEM14,
    EV_USE_ITEM15,

    EV_ITEM_RESPAWN,                //Event 40
    EV_ITEM_POP,
    EV_PLAYER_TELEPORT_IN,
    EV_PLAYER_TELEPORT_OUT,

    EV_GRENADE_BOUNCE,		// eventParm will be the soundindex

    EV_GENERAL_SOUND,
    EV_GLOBAL_SOUND,		// no attenuation
    EV_GLOBAL_TEAM_SOUND,

    EV_BULLET_HIT_FLESH,
    EV_BULLET_HIT_WALL,

    EV_MISSILE_HIT,                 //Event 50
    EV_MISSILE_MISS,
    EV_MISSILE_MISS_METAL,
    EV_RAILTRAIL,
    EV_SHOTGUN,
    EV_BULLET,				// otherEntity is the shooter

    EV_PAIN,
    EV_DEATH1,
    EV_DEATH2,
    EV_DEATH3,
    EV_OBITUARY,                    //Event 60

    EV_POWERUP_QUAD,
    EV_POWERUP_BATTLESUIT,
    EV_POWERUP_REGEN,

    EV_GIB_PLAYER,			// gib a previously living player
    EV_SCOREPLUM,			// score plum

    EV_PROXIMITY_MINE_STICK,
    EV_PROXIMITY_MINE_TRIGGER,
    EV_KAMIKAZE,			// kamikaze explodes
    EV_OBELISKEXPLODE,		// obelisk explodes
    EV_OBELISKPAIN,			// obelisk is in pain
    EV_INVUL_IMPACT,		// invulnerability sphere impact
    EV_JUICED,				// invulnerability juiced effect
    EV_LIGHTNINGBOLT,		// lightning bolt bounced of invulnerability sphere

    EV_DEBUG_LINE,
    EV_STOPLOOPINGSOUND,
    EV_TAUNT,
    EV_TAUNT_YES,
    EV_TAUNT_NO,
    EV_TAUNT_FOLLOWME,
    EV_TAUNT_GETFLAG,
    EV_TAUNT_GUARDBASE,
    EV_TAUNT_PATROL

} entity_event_t;


typedef enum {
    GTS_RED_CAPTURE,
    GTS_BLUE_CAPTURE,
    GTS_RED_RETURN,
    GTS_BLUE_RETURN,
    GTS_RED_TAKEN,
    GTS_BLUE_TAKEN,
    GTS_REDOBELISK_ATTACKED,
    GTS_BLUEOBELISK_ATTACKED,
    GTS_REDTEAM_SCORED,
    GTS_BLUETEAM_SCORED,
    GTS_REDTEAM_TOOK_LEAD,
    GTS_BLUETEAM_TOOK_LEAD,
    GTS_TEAMS_ARE_TIED,
    GTS_KAMIKAZE
} global_team_sound_t;

// animations
typedef enum {
    BOTH_DEATH1,
    BOTH_DEAD1,
    BOTH_DEATH2,
    BOTH_DEAD2,
    BOTH_DEATH3,
    BOTH_DEAD3,

    TORSO_GESTURE,

    TORSO_ATTACK,
    TORSO_ATTACK2,

    TORSO_DROP,
    TORSO_RAISE,

    TORSO_STAND,
    TORSO_STAND2,

    LEGS_WALKCR,
    LEGS_WALK,
    LEGS_RUN,
    LEGS_BACK,
    LEGS_SWIM,

    LEGS_JUMP,
    LEGS_LAND,

    LEGS_JUMPB,
    LEGS_LANDB,

    LEGS_IDLE,
    LEGS_IDLECR,

    LEGS_TURN,

    TORSO_GETFLAG,
    TORSO_GUARDBASE,
    TORSO_PATROL,
    TORSO_FOLLOWME,
    TORSO_AFFIRMATIVE,
    TORSO_NEGATIVE,

    //	BOTH_POSE,		// leilei - crappy ui posing code trying

    MAX_ANIMATIONS,

    LEGS_BACKCR,
    LEGS_BACKWALK,
    FLAG_RUN,
    FLAG_STAND,
    FLAG_STAND2RUN,

    MAX_TOTALANIMATIONS
} animNumber_t;


typedef struct animation_s {
    int		firstFrame;
    int		numFrames;
    int		loopFrames;			// 0 to numFrames
    int		frameLerp;			// msec between frames
    int		initialLerp;		// msec to get to first frame
    int		reversed;			// true if animation is reversed
    int		flipflop;			// true if animation should flipflop back to base
} animation_t;


// flip the togglebit every time an animation
// changes so a restart of the same anim can be detected
#define	ANIM_TOGGLEBIT		128


typedef enum {
    TEAM_FREE,
    TEAM_RED,
    TEAM_BLUE,
    TEAM_SPECTATOR,

    TEAM_NUM_TEAMS
} team_t;

// This is a fair assumption for Double Domination:
#define TEAM_NONE TEAM_SPECTATOR

// Time between location updates
#define TEAM_LOCATION_UPDATE_TIME		1000

// How many players on the overlay
#define TEAM_MAXOVERLAY		32

//team task
typedef enum {
    TEAMTASK_NONE,
    TEAMTASK_OFFENSE, 
    TEAMTASK_DEFENSE,
    TEAMTASK_PATROL,
    TEAMTASK_FOLLOW,
    TEAMTASK_RETRIEVE,
    TEAMTASK_ESCORT,
    TEAMTASK_CAMP
} teamtask_t;

// means of death
typedef enum {
    MOD_UNKNOWN,
    MOD_SHOTGUN,
    MOD_GAUNTLET,
    MOD_MACHINEGUN,
    MOD_GRENADE,
    MOD_GRENADE_SPLASH,
    MOD_ROCKET,
    MOD_ROCKET_SPLASH,
    MOD_PLASMA,
    MOD_PLASMA_SPLASH,
    MOD_RAILGUN,
    MOD_LIGHTNING,
    MOD_BFG,
    MOD_BFG_SPLASH,
    MOD_WATER,
    MOD_SLIME,
    MOD_LAVA,
    MOD_CRUSH,
    MOD_TELEFRAG,
    MOD_FALLING,
    MOD_SUICIDE,
    MOD_TARGET_LASER,
    MOD_TRIGGER_HURT,
    MOD_NAIL,
    MOD_CHAINGUN,
    MOD_PROXIMITY_MINE,
    MOD_KAMIKAZE,
    MOD_JUICED,
    MOD_GRAPPLE
} meansOfDeath_t;


//---------------------------------------------------------

// gitem_t->type
typedef enum {
    IT_BAD,
    IT_WEAPON,				// EFX: rotate + upscale + minlight
    IT_AMMO,				// EFX: rotate
    IT_ARMOR,				// EFX: rotate + minlight
    IT_HEALTH,				// EFX: static external sphere + rotating internal
    IT_POWERUP,				// instant on, timer based
    // EFX: rotate + external ring that rotates
    IT_HOLDABLE,			// single use, holdable item
    // EFX: rotate + bob
    IT_PERSISTANT_POWERUP,
    IT_TEAM
} itemType_t;

#define MAX_ITEM_MODELS 4

typedef struct gitem_s {
    char		*classname;	// spawning name
    char		*pickup_sound;
    char		*world_model[MAX_ITEM_MODELS];

    char		*icon;
    char		*pickup_name;	// for printing on pickup

    int			quantity;		// for ammo how much, or duration of powerup
    itemType_t  giType;			// IT_* flags

    int			giTag;

    char		*precaches;		// string of all models and images this item will use
    char		*sounds;		// string of all sounds this item will use
} gitem_t;

// included in both the game dll and the client
extern	gitem_t	bg_itemlist[];
extern	int		bg_numItems;

gitem_t	*BG_FindItem( const char *pickupName );
gitem_t	*BG_FindItemForWeapon( weapon_t weapon );
gitem_t	*BG_FindItemForPowerup( powerup_t pw );
gitem_t	*BG_FindItemForHoldable( holdable_t pw );
#define	ITEM_INDEX(x) ((x)-bg_itemlist)

qboolean	BG_CanItemBeGrabbed( int gametype, const entityState_t *ent, const playerState_t *ps );


// g_dmflags->integer flags
#define	DF_NO_FALLING			8
#define DF_FIXED_FOV			16
#define	DF_NO_FOOTSTEPS			32
#define DF_INSTANT_WEAPON_CHANGE        64
#define DF_NO_BUNNY                     128
#define DF_INVIS                        256
#define DF_LIGHT_VOTING                 512
#define DF_NO_SELF_DAMAGE               1024
#define DF_PLAYER_OVERLAY               2048

//g_videoflags->integer
#define VF_LOCK_CVARS_BASIC             1
#define VF_LOCK_CVARS_EXTENDED          2
#define VF_LOCK_VERTEX                  4

// g_elimflags->integer
//This is used to signal the client that it cannot go to free spectator:
#define EF_ONEWAY                       1
#define EF_NO_FREESPEC                  2

//g_voteflags->integer
//Autoparsed from allowedvote
//List: "/map_restart/nextmap/map/g_gametype/kick/clientkick/g_doWarmup/timelimit/fraglimit/custom/shuffle/"
#define VF_map_restart  1
#define VF_nextmap      2
#define VF_map          4
#define VF_g_gametype   8
//Note that we skipped kick... not needed
#define VF_clientkick   16
#define VF_g_doWarmup   32
#define VF_timelimit    64
#define VF_fraglimit    128
#define VF_custom       256
#define VF_shuffle      512

// content masks
#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_BODY)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE)


//
// entityState_t->eType
//
typedef enum {
    ET_GENERAL,
    ET_PLAYER,
    ET_ITEM,
    ET_MISSILE,
    ET_MOVER,
    ET_BEAM,
    ET_PORTAL,
    ET_SPEAKER,
    ET_PUSH_TRIGGER,
    ET_TELEPORT_TRIGGER,
    ET_INVISIBLE,
    ET_GRAPPLE,				// grapple hooked on wall
    ET_TEAM,

    ET_EVENTS				// any of the EV_* events can be added freestanding
        // by setting eType to ET_EVENTS + eventNum
        // this avoids having to set eFlags and eventNum
} entityType_t;

//KK-OAX Using this now instead of g_mem.c
// bg_alloc.c
//
qboolean BG_CanAlloc( unsigned int size );
void    *BG_Alloc( unsigned int size );
void    BG_InitMemory( void );
void    BG_Free( void *ptr );
void    BG_DefragmentMemory( void );


void	BG_EvaluateTrajectory( const trajectory_t *tr, int atTime, vec3_t result );
void	BG_EvaluateTrajectoryDelta( const trajectory_t *tr, int atTime, vec3_t result );

void	BG_AddPredictableEventToPlayerstate( int newEvent, int eventParm, playerState_t *ps );

void	BG_TouchJumpPad( playerState_t *ps, entityState_t *jumppad );

void	BG_PlayerStateToEntityState( playerState_t *ps, entityState_t *s, qboolean snap );
void	BG_PlayerStateToEntityStateExtraPolate( playerState_t *ps, entityState_t *s, int time, qboolean snap );

qboolean	BG_PlayerTouchesItem( playerState_t *ps, entityState_t *item, int atTime );


#define ARENAS_PER_TIER		4
#define MAX_ARENAS			1024
#define	MAX_ARENAS_TEXT		8192

#define MAX_BOTS			1024
#define MAX_BOTS_TEXT		8192


// Kamikaze

// 1st shockwave times
#define KAMI_SHOCKWAVE_STARTTIME		0
#define KAMI_SHOCKWAVEFADE_STARTTIME	1500
#define KAMI_SHOCKWAVE_ENDTIME			2000
// explosion/implosion times
#define KAMI_EXPLODE_STARTTIME			250
#define KAMI_IMPLODE_STARTTIME			2000
#define KAMI_IMPLODE_ENDTIME			2250
// 2nd shockwave times
#define KAMI_SHOCKWAVE2_STARTTIME		2000
#define KAMI_SHOCKWAVE2FADE_STARTTIME	2500
#define KAMI_SHOCKWAVE2_ENDTIME			3000
// radius of the models without scaling
#define KAMI_SHOCKWAVEMODEL_RADIUS		88
#define KAMI_BOOMSPHEREMODEL_RADIUS		72
// maximum radius of the models during the effect
#define KAMI_SHOCKWAVE_MAXRADIUS		1320
#define KAMI_BOOMSPHERE_MAXRADIUS		720
#define KAMI_SHOCKWAVE2_MAXRADIUS		704

//KK-OAX
//bg_misc.c
char *BG_TeamName( team_t team );

#endif

/*
   ===========================================================================
   Copyright (C) 1999-2005 Id Software, Inc.

   This file is part of Quake III Arena source code.

   Quake III Arena source code is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the License,
   or (at your option) any later version.

   Quake III Arena source code is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Quake III Arena source code; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
   ===========================================================================
   */
//


#define	CMD_BACKUP			64	
#define	CMD_MASK			(CMD_BACKUP - 1)
// allow a lot of command backups for very fast systems
// multiple commands may be combined into a single packet, so this
// needs to be larger than PACKET_BACKUP


#define	MAX_ENTITIES_IN_SNAPSHOT	256

// snapshots are a view of the server at a given time

// Snapshots are generated at regular time intervals by the server,
// but they may not be sent if a client's rate level is exceeded, or
// they may be dropped by the network.
typedef struct {
    int				snapFlags;			// SNAPFLAG_RATE_DELAYED, etc
    int				ping;

    int				serverTime;		// server time the message is valid for (in msec)

    byte			areamask[MAX_MAP_AREA_BYTES];		// portalarea visibility bits

    playerState_t	ps;						// complete information about the current player at this time

    int				numEntities;			// all of the entities that need to be presented
    entityState_t	entities[MAX_ENTITIES_IN_SNAPSHOT];	// at the time of this snapshot

    int				numServerCommands;		// text based server commands to execute when this
    int				serverCommandSequence;	// snapshot becomes current
} snapshot_t;

enum {
    CGAME_EVENT_NONE,
    CGAME_EVENT_TEAMMENU,
    CGAME_EVENT_SCOREBOARD,
    CGAME_EVENT_EDITHUD
};


/*
   ==================================================================

   functions imported from the main executable

   ==================================================================
   */

#define	CGAME_IMPORT_API_VERSION	4


/*
   ==================================================================

   functions exported to the main executable

   ==================================================================
   */

typedef enum {
    CG_INIT,
    //	void CG_Init( int serverMessageNum, int serverCommandSequence, int clientNum )
    // called when the level loads or when the renderer is restarted
    // all media should be registered at this time
    // cgame will display loading status by calling SCR_Update, which
    // will call CG_DrawInformation during the loading process
    // reliableCommandSequence will be 0 on fresh loads, but higher for
    // demos, tourney restarts, or vid_restarts

    CG_SHUTDOWN,
    //	void (*CG_Shutdown)( void );
    // oportunity to flush and close any open files

    CG_CONSOLE_COMMAND,
    //	qboolean (*CG_ConsoleCommand)( void );
    // a console command has been issued locally that is not recognized by the
    // main game system.
    // use Cmd_Argc() / Cmd_Argv() to read the command, return qfalse if the
    // command is not known to the game

    CG_DRAW_ACTIVE_FRAME,
    //	void (*CG_DrawActiveFrame)( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback );
    // Generates and draws a game scene and status information at the given time.
    // If demoPlayback is set, local movement prediction will not be enabled

    CG_CROSSHAIR_PLAYER,
    //	int (*CG_CrosshairPlayer)( void );

    CG_LAST_ATTACKER,
    //	int (*CG_LastAttacker)( void );

    CG_KEY_EVENT, 
    //	void	(*CG_KeyEvent)( int key, qboolean down );

    CG_MOUSE_EVENT,
    //	void	(*CG_MouseEvent)( int dx, int dy );
    CG_EVENT_HANDLING
        //	void (*CG_EventHandling)(int type);
} cgameExport_t;

//----------------------------------------------

/*
   ===========================================================================
   Copyright (C) 2008-2009 Poul Sander

   This file is part of Open Arena source code.

   Open Arena source code is free software; you can redistribute it
   and/or modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the License,
   or (at your option) any later version.

   Open Arena source code is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Open Arena source code; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
   ===========================================================================
   */

/**
 * This is a list of challenges that a player can only complete while playing
 * against human opponents, either LAN or Internet.
 *
 * Hopefully this will make it a little more fun to play online even if you
 * are not good enough to win you can still track your progress.
 */

#define CHALLENGES_MAX_COUNT	MAX_INT-1
#define CHALLENGES_MAX          2048

#define GENERAL_TEST		0
#define GENERAL_TOTALKILLS      1
#define GENERAL_TOTALDEATHS     2
#define GENERAL_TOTALGAMES      3

//Gametypes
#define GAMETYPES_FFA_WINS      101
#define GAMETYPES_TOURNEY_WINS  102
#define GAMETYPES_TDM_WINS      103
#define GAMETYPES_CTF_WINS      104
#define GAMETYPES_1FCTF_WINS    105
#define GAMETYPES_OVERLOAD_WINS 106
#define GAMETYPES_HARVESTER_WINS 107
#define GAMETYPES_ELIMINATION_WINS 108
#define GAMETYPES_CTF_ELIMINATION_WINS 109
#define GAMETYPES_LMS_WINS      110
#define GAMETYPES_DD_WINS       111
#define GAMETYPES_DOM_WINS      112

//Weapons
#define WEAPON_GAUNTLET_KILLS   201
#define WEAPON_MACHINEGUN_KILLS 202
#define WEAPON_SHOTGUN_KILLS    203
#define WEAPON_GRANADE_KILLS    204
#define WEAPON_ROCKET_KILLS     205
#define WEAPON_LIGHTNING_KILLS  206
#define WEAPON_PLASMA_KILLS     207
#define WEAPON_RAIL_KILLS       208
#define WEAPON_BFG_KILLS        209
#define WEAPON_GRAPPLE_KILLS    210
#define WEAPON_CHAINGUN_KILLS   211
#define WEAPON_NAILGUN_KILLS    212
#define WEAPON_MINE_KILLS       213
#define WEAPON_PUSH_KILLS       214
#define WEAPON_INSTANT_RAIL_KILLS 215
#define WEAPON_TELEFRAG_KILLS   216
#define WEAPON_CRUSH_KILLS      217

//Awards
//Gauntlet is not here as it is the same as WEAPON_GAUNTLET_KILLS
#define AWARD_IMPRESSIVE        301
#define AWARD_EXCELLENT          302
#define AWARD_CAPTURE           303
#define AWARD_ASSIST            304
#define AWARD_DEFENCE           305

//Powerups
#define POWERUP_QUAD_KILL       401
#define POWERUP_SPEED_KILL      402
#define POWERUP_FLIGHT_KILL     403
#define POWERUP_INVIS_KILL      404
#define POWERUP_MULTI_KILL      405
#define POWERUP_COUNTER_QUAD    406
#define POWERUP_COUNTER_SPEED   407
#define POWERUP_COUNTER_FLIGHT  408
#define POWERUP_COUNTER_INVIS   409
#define POWERUP_COUNTER_ENVIR   410
#define POWERUP_COUNTER_REGEN   411
#define POWERUP_COUNTER_MULTI   412

//FFA awards
#define FFA_TOP3                501
//From behind, enemy gets fraglimit-1, player has at most fraglimit-2 but wins anyway
#define FFA_FROMBEHIND          502
//BetterThan: loose a match but have a positive kill ratio against the winner
#define FFA_BETTERTHAN          503
//Get at least half of your kills for players in the best half of the scoreboard
#define FFA_JUDGE               504
//The oppesite
#define FFA_CHEAPKILLER         505

// The entire cgame module is unloaded and reloaded on each level change,
// so there is NO persistant data between levels on the client side.
// If you absolutely need something stored, it can either be kept
// by the server in the server stored userinfos, or stashed in a cvar.

#ifdef MISSIONPACK
#define CG_FONT_THRESHOLD 0.1
#endif

#define	POWERUP_BLINKS		5

#define	POWERUP_BLINK_TIME	1000
#define	FADE_TIME			200
#define	PULSE_TIME			200
#define	DAMAGE_DEFLECT_TIME	100
#define	DAMAGE_RETURN_TIME	400
#define DAMAGE_TIME			500
#define	LAND_DEFLECT_TIME	150
#define	LAND_RETURN_TIME	300
#define	STEP_TIME			200
#define	DUCK_TIME			100
#define	PAIN_TWITCH_TIME	200
#define	WEAPON_SELECT_TIME	1400
#define	ITEM_SCALEUP_TIME	1000
#define	ZOOM_TIME			150
#define	ITEM_BLOB_TIME		200
#define	MUZZLE_FLASH_TIME	20
#define	SINK_TIME			1000		// time for fragments to sink into ground before going away
#define	ATTACKER_HEAD_TIME	10000
#define	REWARD_TIME			3000

#define	PULSE_SCALE			1.5			// amount to scale up the icons when activating

#define	MAX_STEP_CHANGE		32

#define	MAX_VERTS_ON_POLY	10
#define	MAX_MARK_POLYS		256

#define STAT_MINUS			10	// num frame for '-' stats digit

#define	ICON_SIZE			48
#define	CHAR_WIDTH			32
#define	CHAR_HEIGHT			48
#define	TEXT_ICON_SPACE		4

#define	TEAMCHAT_WIDTH		80
#define TEAMCHAT_HEIGHT		8

// very large characters.pk
#define	GIANT_WIDTH			32
#define	GIANT_HEIGHT		48

#define	NUM_CROSSHAIRS		99

#define TEAM_OVERLAY_MAXNAME_WIDTH	12
#define TEAM_OVERLAY_MAXLOCATION_WIDTH	16

#define	DEFAULT_MODEL			"sarge"
#ifdef MISSIONPACK
#define	DEFAULT_TEAM_MODEL		"sergei"
#define	DEFAULT_TEAM_HEAD		"*sergei"
#else
#define	DEFAULT_TEAM_MODEL		"sarge"
#define	DEFAULT_TEAM_HEAD		"sarge"
#endif

#define DEFAULT_REDTEAM_NAME		"Vim supporters"
#define DEFAULT_BLUETEAM_NAME		"Emacs supporters"

typedef enum {
    FOOTSTEP_NORMAL,
    FOOTSTEP_BOOT,
    FOOTSTEP_FLESH,
    FOOTSTEP_MECH,
    FOOTSTEP_ENERGY,
    FOOTSTEP_METAL,
    FOOTSTEP_SPLASH,

    FOOTSTEP_TOTAL
} footstep_t;

typedef enum {
    IMPACTSOUND_DEFAULT,
    IMPACTSOUND_METAL,
    IMPACTSOUND_FLESH
} impactSound_t;

//=================================================

// player entities need to track more information
// than any other type of entity.

// note that not every player entity is a client entity,
// because corpses after respawn are outside the normal
// client numbering range

// when changing animation, set animationTime to frameTime + lerping time
// The current lerp will finish out, then it will lerp to the new animation
typedef struct {
    int			oldFrame;
    int			oldFrameTime;		// time when ->oldFrame was exactly on

    int			frame;
    int			frameTime;			// time when ->frame will be exactly on

    float		backlerp;

    float		yawAngle;
    qboolean	yawing;
    float		pitchAngle;
    qboolean	pitching;

    int			animationNumber;	// may include ANIM_TOGGLEBIT
    animation_t	*animation;
    int			animationTime;		// time when the first frame of the animation will be exact
} lerpFrame_t;


typedef struct {
    lerpFrame_t		legs, torso, flag;
    int				painTime;
    int				painDirection;	// flip from 0 to 1
    int				lightningFiring;

    // railgun trail spawning
    vec3_t			railgunImpact;
    qboolean		railgunFlash;

    // machinegun spinning
    float			barrelAngle;
    int				barrelTime;
    qboolean		barrelSpinning;
} playerEntity_t;

//=================================================



// centity_t have a direct corespondence with gentity_t in the game, but
// only the entityState_t is directly communicated to the cgame
typedef struct centity_s {
    entityState_t	currentState;	// from cg.frame
    entityState_t	nextState;		// from cg.nextFrame, if available
    qboolean		interpolate;	// true if next is valid to interpolate to
    qboolean		currentValid;	// true if cg.frame holds this entity

    int				muzzleFlashTime;	// move to playerEntity?
    int				previousEvent;
    int				teleportFlag;

    int				trailTime;		// so missile trails can handle dropped initial packets
    int				dustTrailTime;
    int				miscTime;

    int				snapShotTime;	// last time this entity was found in a snapshot

    playerEntity_t	pe;

    int				errorTime;		// decay the error from this time
    vec3_t			errorOrigin;
    vec3_t			errorAngles;

    qboolean		extrapolated;	// false if origin / angles is an interpolation
    vec3_t			rawOrigin;
    vec3_t			rawAngles;

    vec3_t			beamEnd;

    // exact interpolated position of entity on this frame
    vec3_t			lerpOrigin;
    vec3_t			lerpAngles;
} centity_t;


static int VectorCompare( const vec3_t v1, const vec3_t v2 ) {
	if (v1[0] != v2[0] || v1[1] != v2[1] || v1[2] != v2[2]) {
		return 0;
	}			
	return 1;
}
//======================================================================

// local entities are created as a result of events or predicted actions,
// and live independantly from all server transmitted entities
typedef struct vm_s vm_t;
struct vm_s {
    // DO NOT MOVE OR CHANGE THESE WITHOUT CHANGING THE VM_OFFSET_* DEFINES
    // USED BY THE ASM CODE
    int			programStack;		// the vm may be recursively entered
    intptr_t			(*systemCall)( intptr_t *parms );

	//------------------------------------
   
	char		name[MAX_QPATH];
	void	*searchPath;				// hint for FS_ReadFileDir()

	// for dynamic linked modules
	void		*dllHandle;
	intptr_t			(QDECL *entryPoint)( int callNum, ... );
	void (*destroy)(vm_t* self);

	// for interpreted modules
	qboolean	currentlyInterpreting;

	qboolean	compiled;
	byte		*codeBase;
	int			entryOfs;
	int			codeLength;

	intptr_t	*instructionPointers;
	int			instructionCount;

	byte		*dataBase;
	int			dataMask;
	int			dataAlloc;			// actually allocated

	int			stackBottom;		// if programStack < stackBottom, error

	int			numSymbols;
	struct vmSymbol_s	*symbols;

	int			callLevel;		// counts recursive VM_Call
	int			breakFunction;		// increment breakCount on function entry to this
	int			breakCount;

	byte		*jumpTableTargets;
	int			numJumpTableTargets;
};
typedef struct markPoly_s {
    struct markPoly_s	*prevMark, *nextMark;
    int			time;
    qhandle_t	markShader;
    qboolean	alphaFade;		// fade alpha instead of rgb
    float		color[4];
    poly_t		poly;
    polyVert_t	verts[MAX_VERTS_ON_POLY];
} markPoly_t;


typedef enum {
    LE_MARK,
    LE_EXPLOSION,
    LE_SPRITE_EXPLOSION,
    LE_FRAGMENT,
    LE_MOVE_SCALE_FADE,
    LE_FALL_SCALE_FADE,
    LE_FADE_RGB,
    LE_SCALE_FADE,
    LE_SCOREPLUM,
    LE_KAMIKAZE,
    LE_INVULIMPACT,
    LE_INVULJUICED,
    LE_SHOWREFENTITY,
    LE_GORE
} leType_t;

typedef enum {
    LEF_PUFF_DONT_SCALE  = 0x0001,			// do not scale size over time
    LEF_TUMBLE			 = 0x0002,			// tumble over time, used for ejecting shells
    LEF_SOUND1			 = 0x0004,			// sound 1 for kamikaze
    LEF_SOUND2			 = 0x0008			// sound 2 for kamikaze
} leFlag_t;

typedef enum {
    LEMT_NONE,
    LEMT_BURN,
    LEMT_BLOOD
} leMarkType_t;			// fragment local entities can leave marks on walls

typedef enum {
    LEBS_NONE,
    LEBS_BLOOD,
    LEBS_BRASS,
    LEBS_SHELL
} leBounceSoundType_t;	// fragment local entities can make sounds on impacts

typedef struct localEntity_s {
    struct localEntity_s	*prev, *next;
    leType_t		leType;
    int				leFlags;

    int				startTime;
    int				endTime;
    int				fadeInTime;

    float			lifeRate;			// 1.0 / (endTime - startTime)

    trajectory_t	pos;
    trajectory_t	angles;

    float			bounceFactor;		// 0.0 = no bounce, 1.0 = perfect

    float			color[4];

    float			radius;

    float			light;
    vec3_t			lightColor;

    leMarkType_t		leMarkType;		// mark to leave on fragment impact
    leBounceSoundType_t	leBounceSoundType;

    refEntity_t		refEntity;		
} localEntity_t;

//======================================================================


typedef struct {
    int				client;
    int				score;
    int				ping;
    int				time;
    int				scoreFlags;
    int				powerUps;
    int				accuracy;
    int				impressiveCount;
    int				excellentCount;
    int				guantletCount;
    int				defendCount;
    int				assistCount;
    int				captures;
    qboolean	perfect;
    int				team;
    int			isDead;
} score_t;

// each client has an associated clientInfo_t
// that contains media references necessary to present the
// client model and other color coded effects
// this is regenerated each time a client's configstring changes,
// usually as a result of a userinfo (name, model, etc) change
#define	MAX_CUSTOM_SOUNDS	32

typedef struct {
    qboolean		infoValid;

    char			name[MAX_QPATH];
    team_t			team;

    int				botSkill;		// 0 = not bot, 1-5 = bot

    vec3_t			color1;
    vec3_t			color2;

    int				score;			// updated by score servercmds
    int				location;		// location index for team mode
    int				health;			// you only get this info about your teammates
    int				armor;
    int				curWeapon;

    int				handicap;
    int				wins, losses;	// in tourney mode

    int				teamTask;		// task in teamplay (offence/defence)
    qboolean		teamLeader;		// true when this is a team leader

    int				powerups;		// so can display quad/flag status

    int				medkitUsageTime;
    int				invulnerabilityStartTime;
    int				invulnerabilityStopTime;

    int				breathPuffTime;

    // when clientinfo is changed, the loading of models/skins/sounds
    // can be deferred until you are dead, to prevent hitches in
    // gameplay
    char			modelName[MAX_QPATH];
    char			skinName[MAX_QPATH];
    char			headModelName[MAX_QPATH];
    char			headSkinName[MAX_QPATH];
    char			redTeam[MAX_TEAMNAME];
    char			blueTeam[MAX_TEAMNAME];
    qboolean		deferred;

    qboolean		newAnims;		// true if using the new mission pack animations
    qboolean		fixedlegs;		// true if legs yaw is always the same as torso yaw
    qboolean		fixedtorso;		// true if torso never changes yaw

    vec3_t			headOffset;		// move head in icon views
    footstep_t		footsteps;
    gender_t		gender;			// from model

    qhandle_t		legsModel;
    qhandle_t		legsSkin;

    qhandle_t		torsoModel;
    qhandle_t		torsoSkin;

    qhandle_t		headModel;
    qhandle_t		headSkin;

    qhandle_t		modelIcon;

    animation_t		animations[MAX_TOTALANIMATIONS];

    sfxHandle_t		sounds[MAX_CUSTOM_SOUNDS];

    int		isDead;
} clientInfo_t;


// each WP_* weapon enum has an associated weaponInfo_t
// that contains media references necessary to present the
// weapon and its effects
typedef struct weaponInfo_s {
    qboolean		registered;
    gitem_t			*item;

    qhandle_t		handsModel;			// the hands don't actually draw, they just position the weapon
    qhandle_t		weaponModel;
    qhandle_t		barrelModel;
    qhandle_t		flashModel;

    vec3_t			weaponMidpoint;		// so it will rotate centered instead of by tag

    float			flashDlight;
    vec3_t			flashDlightColor;
    sfxHandle_t		flashSound[4];		// fast firing weapons randomly choose

    qhandle_t		weaponIcon;
    qhandle_t		ammoIcon;

    qhandle_t		ammoModel;

    qhandle_t		missileModel;
    sfxHandle_t		missileSound;
    void			(*missileTrailFunc)( centity_t *, const struct weaponInfo_s *wi );
    float			missileDlight;
    vec3_t			missileDlightColor;
    int				missileRenderfx;

    void			(*ejectBrassFunc)( centity_t * );

    float			trailRadius;
    float			wiTrailTime;

    sfxHandle_t		readySound;
    sfxHandle_t		firingSound;
    qboolean		loopFireSound;
} weaponInfo_t;


// each IT_* item has an associated itemInfo_t
// that constains media references necessary to present the
// item and its effects
typedef struct {
    qboolean		registered;
    qhandle_t		models[MAX_ITEM_MODELS];
    qhandle_t		icon;
} itemInfo_t;


typedef struct {
    int				itemNum;
} powerupInfo_t;


#define MAX_SKULLTRAIL		10

typedef struct {
    vec3_t positions[MAX_SKULLTRAIL];
    int numpositions;
} skulltrail_t;


#define MAX_REWARDSTACK		10
#define MAX_SOUNDBUFFER		20

//======================================================================

// all cg.stepTime, cg.duckTime, cg.landTime, etc are set to cg.time when the action
// occurs, and they will have visible effects for #define STEP_TIME or whatever msec after

#define MAX_PREDICTED_EVENTS	16

//unlagged - optimized prediction
#define NUM_SAVED_STATES (CMD_BACKUP + 2)
//unlagged - optimized prediction

typedef struct {
    int			clientFrame;		// incremented each frame

    int			clientNum;

    qboolean	demoPlayback;
    qboolean	levelShot;			// taking a level menu screenshot
    int			deferredPlayerLoading;
    qboolean	loading;			// don't defer players at initial startup
    qboolean	intermissionStarted;	// don't play voice rewards, because game will end shortly

    // there are only one or two snapshot_t that are relevent at a time
    int			latestSnapshotNum;	// the number of snapshots the client system has received
    int			latestSnapshotTime;	// the time from latestSnapshotNum, so we don't need to read the snapshot yet

    snapshot_t	*snap;				// cg.snap->serverTime <= cg.time
    snapshot_t	*nextSnap;			// cg.nextSnap->serverTime > cg.time, or NULL
    snapshot_t	activeSnapshots[2];

    float		frameInterpolation;	// (float)( cg.time - cg.frame->serverTime ) / (cg.nextFrame->serverTime - cg.frame->serverTime)

    qboolean	thisFrameTeleport;
    qboolean	nextFrameTeleport;

    int			frametime;		// cg.time - cg.oldTime

    int			time;			// this is the time value that the client
    // is rendering at.
    int			oldTime;		// time at last frame, used for missile trails and prediction checking

    int			physicsTime;	// either cg.snap->time or cg.nextSnap->time

    int			timelimitWarnings;	// 5 min, 1 min, overtime
    int			fraglimitWarnings;

    qboolean	mapRestart;			// set on a map restart to set back the weapon

    qboolean	renderingThirdPerson;		// during deaths, chasecams, etc

    // prediction state
    qboolean	hyperspace;				// true if prediction has hit a trigger_teleport
    playerState_t	predictedPlayerState;
    centity_t		predictedPlayerEntity;
    qboolean	validPPS;				// clear until the first call to CG_PredictPlayerState
    int			predictedErrorTime;
    vec3_t		predictedError;

    int			eventSequence;
    int			predictableEvents[MAX_PREDICTED_EVENTS];

    float		stepChange;				// for stair up smoothing
    int			stepTime;

    float		duckChange;				// for duck viewheight smoothing
    int			duckTime;

    float		landChange;				// for landing hard
    int			landTime;

    // input state sent to server
    int			weaponSelect;

    // auto rotating items
    vec3_t		autoAngles;
    vec3_t		autoAxis[3];
    vec3_t		autoAnglesFast;
    vec3_t		autoAxisFast[3];

    // view rendering
    refdef_t	refdef;
    vec3_t		refdefViewAngles;		// will be converted to refdef.viewaxis

    // zoom key
    qboolean	zoomed;
    int			zoomTime;
    float		zoomSensitivity;

    // information screen text during loading
    char		infoScreenText[MAX_STRING_CHARS];

    // scoreboard
    int			scoresRequestTime;
    int			numScores;
    int			selectedScore;
    int			teamScores[2];
    score_t		scores[MAX_CLIENTS];
    qboolean	showScores;
    qboolean	scoreBoardShowing;
    int			scoreFadeTime;

    int		accuracys[WP_NUM_WEAPONS][2];
    int		accRequestTime;
    qboolean	showAcc;
    qboolean	accBoardShowing;
    int		accFadeTime;


    char		killerName[MAX_NAME_LENGTH];
    char			spectatorList[MAX_STRING_CHARS];		// list of names
    int				spectatorLen;												// length of list
    float			spectatorWidth;											// width in device units
    int				spectatorTime;											// next time to offset
    int				spectatorPaintX;										// current paint x
    int				spectatorPaintX2;										// current paint x
    int				spectatorOffset;										// current offset from start
    int				spectatorPaintLen; 									// current offset from start

    // skull trails
    skulltrail_t	skulltrails[MAX_CLIENTS];

    // centerprinting
    int			centerPrintTime;
    int			centerPrintCharWidth;
    int			centerPrintY;
    char		centerPrint[1024];
    int			centerPrintLines;

    // low ammo warning state
    int			lowAmmoWarning;		// 1 = low, 2 = empty

    // kill timers for carnage reward
    int			lastKillTime;

    // crosshair client ID
    int			crosshairClientNum;
    int			crosshairClientTime;

    // powerup active flashing
    int			powerupActive;
    int			powerupTime;

    // attacking player
    int			attackerTime;
    int			voiceTime;

    // reward medals
    int			rewardStack;
    int			rewardTime;
    int			rewardCount[MAX_REWARDSTACK];
    qhandle_t	rewardShader[MAX_REWARDSTACK];
    qhandle_t	rewardSound[MAX_REWARDSTACK];

    // sound buffer mainly for announcer sounds
    int			soundBufferIn;
    int			soundBufferOut;
    int			soundTime;
    qhandle_t	soundBuffer[MAX_SOUNDBUFFER];

    // for voice chat buffer
    int			voiceChatTime;
    int			voiceChatBufferIn;
    int			voiceChatBufferOut;

    // warmup countdown
    int			warmup;
    int			warmupCount;

    //==========================

    int			itemPickup;
    int			itemPickupTime;
    int			itemPickupBlendTime;	// the pulse around the crosshair is timed seperately

    int			weaponSelectTime;
    int			weaponAnimation;
    int			weaponAnimationTime;

    // blend blobs
    float		damageTime;
    float		damageX, damageY, damageValue;

    // status bar head
    float		headYaw;
    float		headEndPitch;
    float		headEndYaw;
    int			headEndTime;
    float		headStartPitch;
    float		headStartYaw;
    int			headStartTime;

    // view movement
    float		v_dmg_time;
    float		v_dmg_pitch;
    float		v_dmg_roll;

    vec3_t		kick_angles;	// weapon kicks
    vec3_t		kick_origin;

    // temp working variables for player view
    float		bobfracsin;
    int			bobcycle;
    float		xyspeed;
    int     nextOrbitTime;

    //qboolean cameraMode;		// if rendering from a loaded camera


    // development tool
    refEntity_t		testModelEntity;
    char			testModelName[MAX_QPATH];
    qboolean		testGun;

    //unlagged - optimized prediction
    int			lastPredictedCommand;
    int			lastServerTime;
    playerState_t savedPmoveStates[NUM_SAVED_STATES];
    int			stateHead, stateTail;
    //unlagged - optimized prediction

    //time that the client will respawn. If 0 = the player is alive.
    int respawnTime;

    int redObeliskHealth;
    int blueObeliskHealth;
} cg_t;


// all of the model, shader, and sound references that are
// loaded at gamestate time are stored in cgMedia_t
// Other media that can be tied to clients, weapons, or items are
// stored in the clientInfo_t, itemInfo_t, weaponInfo_t, and powerupInfo_t
typedef struct {
    qhandle_t	charsetShader;
    qhandle_t	charsetProp;
    qhandle_t	charsetPropGlow;
    qhandle_t	charsetPropB;
    qhandle_t	whiteShader;

    qhandle_t	redCubeModel;
    qhandle_t	blueCubeModel;
    qhandle_t	redCubeIcon;
    qhandle_t	blueCubeIcon;
    qhandle_t	redFlagModel;
    qhandle_t	blueFlagModel;
    qhandle_t	neutralFlagModel;
    qhandle_t	redFlagShader[3];
    qhandle_t	blueFlagShader[3];
    qhandle_t	flagShader[4];

    //For Double Domination:
    //qhandle_t	ddPointA;
    //qhandle_t	ddPointB;
    qhandle_t	ddPointSkinA[4]; //white,red,blue,none
    qhandle_t	ddPointSkinB[4]; //white,red,blue,none

    qhandle_t	flagPoleModel;
    qhandle_t	flagFlapModel;

    qhandle_t	redFlagFlapSkin;
    qhandle_t	blueFlagFlapSkin;
    qhandle_t	neutralFlagFlapSkin;

    qhandle_t	redFlagBaseModel;
    qhandle_t	blueFlagBaseModel;
    qhandle_t	neutralFlagBaseModel;

    qhandle_t	overloadBaseModel;
    qhandle_t	overloadTargetModel;
    qhandle_t	overloadLightsModel;
    qhandle_t	overloadEnergyModel;

    qhandle_t	harvesterModel;
    qhandle_t	harvesterRedSkin;
    qhandle_t	harvesterBlueSkin;
    qhandle_t	harvesterNeutralModel;

    qhandle_t	armorModel;
    qhandle_t	armorIcon;

    qhandle_t	teamStatusBar;

    qhandle_t	deferShader;

    // gib explosions
    qhandle_t	gibAbdomen;
    qhandle_t	gibArm;
    qhandle_t	gibChest;
    qhandle_t	gibFist;
    qhandle_t	gibFoot;
    qhandle_t	gibForearm;
    qhandle_t	gibIntestine;
    qhandle_t	gibLeg;
    qhandle_t	gibSkull;
    qhandle_t	gibBrain;

    qhandle_t	smoke2;

    qhandle_t	machinegunBrassModel;
    qhandle_t	shotgunBrassModel;

    qhandle_t	railRingsShader;
    qhandle_t	railCoreShader;

    qhandle_t	lightningShader;

    qhandle_t	friendShader;

    qhandle_t	balloonShader;
    qhandle_t	connectionShader;

    qhandle_t	selectShader;
    qhandle_t	viewBloodShader;
    qhandle_t	tracerShader;
    qhandle_t	crosshairShader[NUM_CROSSHAIRS];
    qhandle_t	lagometerShader;
    qhandle_t	backTileShader;
    qhandle_t	noammoShader;

    qhandle_t	smokePuffShader;
    qhandle_t	smokePuffRageProShader;
    qhandle_t	shotgunSmokePuffShader;
    qhandle_t	plasmaBallShader;
    qhandle_t	waterBubbleShader;
    qhandle_t	bloodTrailShader;



    // LEILEI shaders

    qhandle_t	lsmkShader1;
    qhandle_t	lsmkShader2;
    qhandle_t	lsmkShader3;
    qhandle_t	lsmkShader4;
    qhandle_t	lbumShader1;
    qhandle_t	lfblShader1;
    qhandle_t	lsplShader;
    qhandle_t	lspkShader1;
    qhandle_t	lspkShader2;
    qhandle_t	lbldShader1;
    qhandle_t	lbldShader2;
    qhandle_t	grappleShader;	// leilei - grapple hook
    qhandle_t	lmarkmetal1;
    qhandle_t	lmarkmetal2;
    qhandle_t	lmarkmetal3;
    qhandle_t	lmarkmetal4;
    qhandle_t	lmarkbullet1;
    qhandle_t	lmarkbullet2;
    qhandle_t	lmarkbullet3;
    qhandle_t	lmarkbullet4;

    //#ifdef MISSIONPACK
    qhandle_t	nailPuffShader;
    qhandle_t	blueProxMine;
    //#endif

    qhandle_t	numberShaders[11];

    qhandle_t	shadowMarkShader;

    qhandle_t	botSkillShaders[5];

    // wall mark shaders
    qhandle_t	wakeMarkShader;
    qhandle_t	bloodMarkShader;
    qhandle_t	bulletMarkShader;
    qhandle_t	burnMarkShader;
    qhandle_t	holeMarkShader;
    qhandle_t	energyMarkShader;

    // powerup shaders
    qhandle_t	quadShader;
    qhandle_t	redQuadShader;
    qhandle_t	quadWeaponShader;
    qhandle_t	invisShader;
    qhandle_t	regenShader;
    qhandle_t	battleSuitShader;
    qhandle_t	battleWeaponShader;
    qhandle_t	hastePuffShader;
    qhandle_t	redKamikazeShader;
    qhandle_t	blueKamikazeShader;

    // player overlays 
    qhandle_t       neutralOverlay;
    qhandle_t       redOverlay;
    qhandle_t       blueOverlay;

    // weapon effect models
    qhandle_t	bulletFlashModel;
    qhandle_t	ringFlashModel;
    qhandle_t	dishFlashModel;
    qhandle_t	lightningExplosionModel;

    // weapon effect shaders
    qhandle_t	railExplosionShader;
    qhandle_t	plasmaExplosionShader;
    qhandle_t	bulletExplosionShader;
    qhandle_t	rocketExplosionShader;
    qhandle_t	grenadeExplosionShader;
    qhandle_t	bfgExplosionShader;
    qhandle_t	bloodExplosionShader;

    // special effects models
    qhandle_t	teleportEffectModel;
    qhandle_t	teleportEffectShader;
    //#ifdef MISSIONPACK
    qhandle_t	kamikazeEffectModel;
    qhandle_t	kamikazeShockWave;
    qhandle_t	kamikazeHeadModel;
    qhandle_t	kamikazeHeadTrail;
    qhandle_t	guardPowerupModel;
    qhandle_t	scoutPowerupModel;
    qhandle_t	doublerPowerupModel;
    qhandle_t	ammoRegenPowerupModel;
    qhandle_t	invulnerabilityImpactModel;
    qhandle_t	invulnerabilityJuicedModel;
    qhandle_t	medkitUsageModel;
    qhandle_t	dustPuffShader;
    qhandle_t	heartShader;
    //#endif
    qhandle_t	invulnerabilityPowerupModel;

    // scoreboard headers
    qhandle_t	scoreboardName;
    qhandle_t	scoreboardPing;
    qhandle_t	scoreboardScore;
    qhandle_t	scoreboardTime;

    // medals shown during gameplay
    qhandle_t	medalImpressive;
    qhandle_t	medalExcellent;
    qhandle_t	medalGauntlet;
    qhandle_t	medalDefend;
    qhandle_t	medalAssist;
    qhandle_t	medalCapture;

    // sounds
    sfxHandle_t	quadSound;
    sfxHandle_t	tracerSound;
    sfxHandle_t	selectSound;
    sfxHandle_t	useNothingSound;
    sfxHandle_t	wearOffSound;
    sfxHandle_t	footsteps[FOOTSTEP_TOTAL][4];
    sfxHandle_t	sfx_lghit1;
    sfxHandle_t	sfx_lghit2;
    sfxHandle_t	sfx_lghit3;
    sfxHandle_t	sfx_ric1;
    sfxHandle_t	sfx_ric2;
    sfxHandle_t	sfx_ric3;
    sfxHandle_t	sfx_railg;
    sfxHandle_t	sfx_rockexp;
    sfxHandle_t	sfx_plasmaexp;
    //#ifdef MISSIONPACK
    sfxHandle_t	sfx_proxexp;
    sfxHandle_t	sfx_nghit;
    sfxHandle_t	sfx_nghitflesh;
    sfxHandle_t	sfx_nghitmetal;
    sfxHandle_t	sfx_chghit;
    sfxHandle_t	sfx_chghitflesh;
    sfxHandle_t	sfx_chghitmetal;
    sfxHandle_t kamikazeExplodeSound;
    sfxHandle_t kamikazeImplodeSound;
    sfxHandle_t kamikazeFarSound;
    sfxHandle_t useInvulnerabilitySound;
    sfxHandle_t invulnerabilityImpactSound1;
    sfxHandle_t invulnerabilityImpactSound2;
    sfxHandle_t invulnerabilityImpactSound3;
    sfxHandle_t invulnerabilityJuicedSound;
    sfxHandle_t obeliskHitSound1;
    sfxHandle_t obeliskHitSound2;
    sfxHandle_t obeliskHitSound3;
    sfxHandle_t	obeliskRespawnSound;
    sfxHandle_t	winnerSound;
    sfxHandle_t	loserSound;
    sfxHandle_t	youSuckSound;
    //#endif
    sfxHandle_t	gibSound;
    sfxHandle_t	gibBounce1Sound;
    sfxHandle_t	gibBounce2Sound;
    sfxHandle_t	gibBounce3Sound;
    sfxHandle_t	teleInSound;
    sfxHandle_t	teleOutSound;
    sfxHandle_t	noAmmoSound;
    sfxHandle_t	respawnSound;
    sfxHandle_t talkSound;
    sfxHandle_t landSound;
    sfxHandle_t fallSound;
    sfxHandle_t jumpPadSound;

    // LEILEI
    sfxHandle_t	lspl1Sound;
    sfxHandle_t	lspl2Sound; // Blood Splat Noises
    sfxHandle_t	lspl3Sound;

    sfxHandle_t	lbul1Sound;
    sfxHandle_t	lbul2Sound;	// Bullet Drop Noises
    sfxHandle_t	lbul3Sound;

    sfxHandle_t	lshl1Sound;
    sfxHandle_t	lshl2Sound; // Shell Drop Noises
    sfxHandle_t	lshl3Sound;

    // LEILEI END

    sfxHandle_t oneMinuteSound;
    sfxHandle_t fiveMinuteSound;
    sfxHandle_t suddenDeathSound;

    sfxHandle_t threeFragSound;
    sfxHandle_t twoFragSound;
    sfxHandle_t oneFragSound;

    sfxHandle_t hitSound;
    sfxHandle_t hitSoundHighArmor;
    sfxHandle_t hitSoundLowArmor;
    sfxHandle_t hitTeamSound;
    sfxHandle_t impressiveSound;
    sfxHandle_t excellentSound;
    sfxHandle_t deniedSound;
    sfxHandle_t humiliationSound;
    sfxHandle_t assistSound;
    sfxHandle_t defendSound;
    sfxHandle_t firstImpressiveSound;
    sfxHandle_t firstExcellentSound;
    sfxHandle_t firstHumiliationSound;

    sfxHandle_t takenLeadSound;
    sfxHandle_t tiedLeadSound;
    sfxHandle_t lostLeadSound;

    sfxHandle_t voteNow;
    sfxHandle_t votePassed;
    sfxHandle_t voteFailed;

    sfxHandle_t watrInSound;
    sfxHandle_t watrOutSound;
    sfxHandle_t watrUnSound;

    sfxHandle_t flightSound;
    sfxHandle_t medkitSound;

    sfxHandle_t weaponHoverSound;

    // teamplay sounds
    sfxHandle_t captureAwardSound;
    sfxHandle_t redScoredSound;
    sfxHandle_t blueScoredSound;
    sfxHandle_t redLeadsSound;
    sfxHandle_t blueLeadsSound;
    sfxHandle_t teamsTiedSound;

    sfxHandle_t	captureYourTeamSound;
    sfxHandle_t	captureOpponentSound;
    sfxHandle_t	returnYourTeamSound;
    sfxHandle_t	returnOpponentSound;
    sfxHandle_t	takenYourTeamSound;
    sfxHandle_t	takenOpponentSound;

    sfxHandle_t redFlagReturnedSound;
    sfxHandle_t blueFlagReturnedSound;
    sfxHandle_t neutralFlagReturnedSound;
    sfxHandle_t	enemyTookYourFlagSound;
    sfxHandle_t	enemyTookTheFlagSound;
    sfxHandle_t yourTeamTookEnemyFlagSound;
    sfxHandle_t yourTeamTookTheFlagSound;
    sfxHandle_t	youHaveFlagSound;
    sfxHandle_t yourBaseIsUnderAttackSound;
    sfxHandle_t holyShitSound;

    // tournament sounds
    sfxHandle_t	count3Sound;
    sfxHandle_t	count2Sound;
    sfxHandle_t	count1Sound;
    sfxHandle_t	countFightSound;
    sfxHandle_t	countPrepareSound;

#ifdef MISSIONPACK
    // new stuff
    qhandle_t patrolShader;
    qhandle_t assaultShader;
    qhandle_t campShader;
    qhandle_t followShader;
    qhandle_t defendShader;
    qhandle_t teamLeaderShader;
    qhandle_t retrieveShader;
    qhandle_t escortShader;
    qhandle_t deathShader;
    qhandle_t flagShaders[3];
    sfxHandle_t	countPrepareTeamSound;
#endif

    sfxHandle_t ammoregenSound;
    sfxHandle_t doublerSound;
    sfxHandle_t guardSound;
    sfxHandle_t scoutSound;

    qhandle_t cursor;
    qhandle_t selectCursor;
    qhandle_t sizeCursor;

    sfxHandle_t	regenSound;
    sfxHandle_t	protectSound;
    sfxHandle_t	n_healthSound;
    sfxHandle_t	hgrenb1aSound;
    sfxHandle_t	hgrenb2aSound;
    sfxHandle_t	wstbimplSound;
    sfxHandle_t	wstbimpmSound;
    sfxHandle_t	wstbimpdSound;
    sfxHandle_t	wstbactvSound;

} cgMedia_t;


// The client game static (cgs) structure hold everything
// loaded or calculated from the gamestate.  It will NOT
// be cleared when a tournement restart is done, allowing
// all clients to begin playing instantly
typedef struct {
    gameState_t		gameState;			// gamestate from server
    glconfig_t		glconfig;			// rendering configuration
    float			screenXScale;		// derived from glconfig
    float			screenYScale;
    float			screenXBias;

    int				serverCommandSequence;	// reliable command stream counter
    int				processedSnapshotNum;// the number of snapshots cgame has requested

    qboolean		localServer;		// detected on startup by checking sv_running

    // parsed from serverinfo
    gametype_t		gametype;
    int				dmflags;
    int                             videoflags;
    int				elimflags;
    int				teamflags;
    int				fraglimit;
    int				capturelimit;
    int				timelimit;
    int				maxclients;
    char			mapname[MAX_QPATH];
    char			redTeam[MAX_QPATH];
    char			blueTeam[MAX_QPATH];

    int				voteTime;
    int				voteYes;
    int				voteNo;
    qboolean		voteModified;			// beep whenever changed
    char			voteString[MAX_STRING_TOKENS];

    int				teamVoteTime[2];
    int				teamVoteYes[2];
    int				teamVoteNo[2];
    qboolean		teamVoteModified[2];	// beep whenever changed
    char			teamVoteString[2][MAX_STRING_TOKENS];

    int				levelStartTime;

    //Forced FFA
    int			ffa_gt;

    //Elimination
    int				roundStartTime;	
    int				roundtime;

    //CTF Elimination
    int				attackingTeam;

    //Last Man Standing
    int				lms_mode;

    //instantgib + nexuiz style rocket arena:
    int				nopickup;

    //Double Domination DD
    int 				timetaken;

    //Domination
    int domination_points_count;
    char domination_points_names[MAX_DOMINATION_POINTS][MAX_DOMINATION_POINTS_NAMES];
    int domination_points_status[MAX_DOMINATION_POINTS];


    int				scores1, scores2;		// from configstrings
    int				redflag, blueflag;		// flag status from configstrings
    int				flagStatus;

    qboolean  newHud;

    //
    // locally derived information from gamestate
    //
    qhandle_t		gameModels[MAX_MODELS];
    sfxHandle_t		gameSounds[MAX_SOUNDS];

    int				numInlineModels;
    qhandle_t		inlineDrawModel[MAX_MODELS];
    vec3_t			inlineModelMidpoints[MAX_MODELS];

    clientInfo_t	clientinfo[MAX_CLIENTS];

    // teamchat width is *3 because of embedded color codes
    char			teamChatMsgs[TEAMCHAT_HEIGHT][TEAMCHAT_WIDTH*3+1];
    int				teamChatMsgTimes[TEAMCHAT_HEIGHT];
    int				teamChatPos;
    int				teamLastChatPos;

    int cursorX;
    int cursorY;
    qboolean eventHandling;
    qboolean mouseCaptured;
    qboolean sizingHud;
    void *capturedItem;
    qhandle_t activeCursor;

    // orders
    int currentOrder;
    qboolean orderPending;
    int orderTime;
    int currentVoiceClient;
    int acceptOrderTime;
    int acceptTask;
    int acceptLeader;
    char acceptVoice[MAX_NAME_LENGTH];

    // media
    cgMedia_t		media;

    //unlagged - client options
    // this will be set to the server's g_delagHitscan
    int				delagHitscan;
    //unlagged - client options
    //KK-OAX For storing whether or not the server has multikills enabled. 
    int             altExcellent;
} cgs_t;

//==============================================================================

extern	cgs_t			cgs;
extern	cg_t			cg;
extern	centity_t		cg_entities[MAX_GENTITIES];
extern	weaponInfo_t	cg_weapons[MAX_WEAPONS];
extern	itemInfo_t		cg_items[MAX_ITEMS];
extern	markPoly_t		cg_markPolys[MAX_MARK_POLYS];

extern	vmCvar_t		cg_centertime;
extern	vmCvar_t		cg_runpitch;
extern	vmCvar_t		cg_runroll;
extern	vmCvar_t		cg_bobup;
extern	vmCvar_t		cg_bobpitch;
extern	vmCvar_t		cg_bobroll;
extern	vmCvar_t		cg_swingSpeed;
extern	vmCvar_t		cg_shadows;
extern	vmCvar_t		cg_gibs;
extern	vmCvar_t		cg_drawTimer;
extern	vmCvar_t		cg_drawFPS;
extern	vmCvar_t		cg_drawSnapshot;
extern	vmCvar_t		cg_draw3dIcons;
extern	vmCvar_t		cg_drawIcons;
extern	vmCvar_t		cg_drawAmmoWarning;
extern	vmCvar_t		cg_drawCrosshair;
extern	vmCvar_t		cg_drawCrosshairNames;
extern	vmCvar_t		cg_drawRewards;
extern	vmCvar_t		cg_drawTeamOverlay;
extern	vmCvar_t		cg_teamOverlayUserinfo;
extern	vmCvar_t		cg_crosshairX;
extern	vmCvar_t		cg_crosshairY;
extern	vmCvar_t		cg_crosshairSize;
extern	vmCvar_t		cg_crosshairHealth;
extern	vmCvar_t		cg_drawStatus;
extern	vmCvar_t		cg_draw2D;
extern	vmCvar_t		cg_animSpeed;
extern	vmCvar_t		cg_debugAnim;
extern	vmCvar_t		cg_debugPosition;
extern	vmCvar_t		cg_debugEvents;
extern	vmCvar_t		cg_railTrailTime;
extern	vmCvar_t		cg_errorDecay;
extern	vmCvar_t		cg_nopredict;
extern	vmCvar_t		cg_noPlayerAnims;
extern	vmCvar_t		cg_showmiss;
extern	vmCvar_t		cg_footsteps;
extern	vmCvar_t		cg_addMarks;
extern	vmCvar_t		cg_brassTime;
extern	vmCvar_t		cg_gun_frame;
extern	vmCvar_t		cg_gun_x;
extern	vmCvar_t		cg_gun_y;
extern	vmCvar_t		cg_gun_z;
extern	vmCvar_t		cg_drawGun;
extern	vmCvar_t		cg_viewsize;
extern	vmCvar_t		cg_tracerChance;
extern	vmCvar_t		cg_tracerWidth;
extern	vmCvar_t		cg_tracerLength;
extern	vmCvar_t		cg_autoswitch;
extern	vmCvar_t		cg_ignore;
extern	vmCvar_t		cg_simpleItems;
extern	vmCvar_t		cg_fov;
extern	vmCvar_t		cg_zoomFov;
extern	vmCvar_t		cg_thirdPersonRange;
extern	vmCvar_t		cg_thirdPersonAngle;
extern	vmCvar_t		cg_thirdPerson;
extern	vmCvar_t		cg_lagometer;
extern	vmCvar_t		cg_drawAttacker;
extern	vmCvar_t		cg_drawSpeed;
extern	vmCvar_t		cg_synchronousClients;
extern	vmCvar_t		cg_teamChatTime;
extern	vmCvar_t		cg_teamChatHeight;
extern	vmCvar_t		cg_stats;
extern	vmCvar_t 		cg_forceModel;
extern	vmCvar_t 		cg_buildScript;
extern	vmCvar_t		cg_paused;
extern	vmCvar_t		cg_blood;
extern	vmCvar_t		cg_predictItems;
extern	vmCvar_t		cg_deferPlayers;
extern	vmCvar_t		cg_drawFriend;
extern	vmCvar_t		cg_teamChatsOnly;
extern	vmCvar_t		cg_noVoiceChats;
extern	vmCvar_t		cg_noVoiceText;
extern  vmCvar_t		cg_scorePlum;
//unlagged - smooth clients #2
// this is done server-side now
//extern	vmCvar_t		cg_smoothClients;
//unlagged - smooth clients #2
extern	vmCvar_t		pmove_fixed;
extern	vmCvar_t		pmove_msec;
extern	vmCvar_t		pmove_float;
//extern	vmCvar_t		cg_pmove_fixed;
extern	vmCvar_t		cg_cameraOrbit;
extern	vmCvar_t		cg_cameraOrbitDelay;
extern	vmCvar_t		cg_timescaleFadeEnd;
extern	vmCvar_t		cg_timescaleFadeSpeed;
extern	vmCvar_t		cg_timescale;
extern	vmCvar_t		cg_cameraMode;
extern  vmCvar_t		cg_smallFont;
extern  vmCvar_t		cg_bigFont;
extern	vmCvar_t		cg_noTaunt;
extern	vmCvar_t		cg_noProjectileTrail;
extern	vmCvar_t		cg_oldRail;
extern	vmCvar_t		cg_oldRocket;

extern	vmCvar_t		cg_leiEnhancement;			// LEILEI'S LINE!
extern	vmCvar_t		cg_leiGoreNoise;			// LEILEI'S LINE!
extern	vmCvar_t		cg_leiBrassNoise;			// LEILEI'S LINE!
extern	vmCvar_t		cg_leiSuperGoreyAwesome;	// LEILEI'S LINE!
extern	vmCvar_t		cg_oldPlasma;
extern	vmCvar_t		cg_trueLightning;
extern	vmCvar_t		cg_music;
#ifdef MISSIONPACK
extern	vmCvar_t		cg_redTeamName;
extern	vmCvar_t		cg_blueTeamName;
extern	vmCvar_t		cg_currentSelectedPlayer;
extern	vmCvar_t		cg_currentSelectedPlayerName;
extern	vmCvar_t		cg_singlePlayer;
extern	vmCvar_t		cg_singlePlayerActive;
extern  vmCvar_t		cg_recordSPDemo;
extern  vmCvar_t		cg_recordSPDemoName;
#endif
//Sago: Moved outside
extern	vmCvar_t		cg_obeliskRespawnDelay;
extern	vmCvar_t		cg_enableDust;
extern	vmCvar_t		cg_enableBreath;

//unlagged - client options
extern	vmCvar_t		cg_delag;
//extern	vmCvar_t		cg_debugDelag;
//extern	vmCvar_t		cg_drawBBox;
extern	vmCvar_t		cg_cmdTimeNudge;
extern	vmCvar_t		sv_fps;
extern	vmCvar_t		cg_projectileNudge;
extern	vmCvar_t		cg_optimizePrediction;
extern	vmCvar_t		cl_timeNudge;
//extern	vmCvar_t		cg_latentSnaps;
//extern	vmCvar_t		cg_latentCmds;
//extern	vmCvar_t		cg_plOut;
//unlagged - client options

//extra CVARS elimination
extern	vmCvar_t		cg_alwaysWeaponBar;
extern	vmCvar_t		cg_hitsound;
extern  vmCvar_t                cg_voip_teamonly;
extern  vmCvar_t                cg_voteflags;
extern  vmCvar_t                cg_cyclegrapple;
extern  vmCvar_t                cg_vote_custom_commands;

extern  vmCvar_t                cg_autovertex;

//Cvar to adjust the size of the fragmessage
extern	vmCvar_t		cg_fragmsgsize;

extern	vmCvar_t		cg_crosshairPulse;
extern	vmCvar_t		cg_differentCrosshairs;
extern	vmCvar_t		cg_ch1;
extern	vmCvar_t		cg_ch1size;
extern	vmCvar_t		cg_ch2;
extern	vmCvar_t		cg_ch2size;
extern	vmCvar_t		cg_ch3;
extern	vmCvar_t		cg_ch3size;
extern	vmCvar_t		cg_ch4;
extern	vmCvar_t		cg_ch4size;
extern	vmCvar_t		cg_ch5;
extern	vmCvar_t		cg_ch5size;
extern	vmCvar_t		cg_ch6;
extern	vmCvar_t		cg_ch6size;
extern	vmCvar_t		cg_ch7;
extern	vmCvar_t		cg_ch7size;
extern	vmCvar_t		cg_ch8;
extern	vmCvar_t		cg_ch8size;
extern	vmCvar_t		cg_ch9;
extern	vmCvar_t		cg_ch9size;
extern	vmCvar_t		cg_ch10;
extern	vmCvar_t		cg_ch10size;
extern	vmCvar_t		cg_ch11;
extern	vmCvar_t		cg_ch11size;
extern	vmCvar_t		cg_ch12;
extern	vmCvar_t		cg_ch12size;
extern	vmCvar_t		cg_ch13;
extern	vmCvar_t		cg_ch13size;

extern	vmCvar_t                cg_crosshairColorRed;
extern	vmCvar_t                cg_crosshairColorGreen;
extern	vmCvar_t                cg_crosshairColorBlue;

extern vmCvar_t			cg_weaponBarStyle;

extern vmCvar_t                 cg_weaponOrder;
extern vmCvar_t			cg_chatBeep;
extern vmCvar_t			cg_teamChatBeep;

//unlagged - cg_unlagged.c
void CG_PredictWeaponEffects( centity_t *cent );
//void CG_AddBoundingBox( centity_t *cent );
qboolean CG_Cvar_ClampInt( const char *name, vmCvar_t *vmCvar, int min, int max );
//unlagged - cg_unlagged.c

//
// cg_main.c
//
const char *CG_ConfigString( int index );
const char *CG_Argv( int arg );

void QDECL CG_Printf( const char *msg, ... );
void QDECL CG_Error( const char *msg, ... ) __attribute__((noreturn));

void CG_StartMusic( void );

void CG_UpdateCvars( void );

int CG_CrosshairPlayer( void );
int CG_LastAttacker( void );
void CG_LoadMenus(const char *menuFile);
void CG_KeyEvent(int key, qboolean down);
void CG_MouseEvent(int x, int y);
void CG_EventHandling(int type);
void CG_RankRunFrame( void );
void CG_SetScoreSelection(void *menu);
//score_t *CG_GetSelectedScore( void );
void CG_BuildSpectatorString( void );

//unlagged, sagos modfication
void SnapVectorTowards( vec3_t v, vec3_t to );

void CG_FairCvars( void );

//
// cg_view.c
//
void CG_TestModel_f (void);
void CG_TestGun_f (void);
void CG_TestModelNextFrame_f (void);
void CG_TestModelPrevFrame_f (void);
void CG_TestModelNextSkin_f (void);
void CG_TestModelPrevSkin_f (void);
void CG_ZoomDown_f( void );
void CG_ZoomUp_f( void );
void CG_AddBufferedSound( sfxHandle_t sfx);

void CG_DrawActiveFrame( int serverTime, stereoFrame_t stereoView, qboolean demoPlayback );


//
// cg_drawtools.c
//
void CG_AdjustFrom640( float *x, float *y, float *w, float *h );
void CG_FillRect( float x, float y, float width, float height, const float *color );
void CG_DrawPic( float x, float y, float width, float height, qhandle_t hShader );
void CG_DrawString( float x, float y, const char *string, 
        float charWidth, float charHeight, const float *modulate );


void CG_DrawStringExt( int x, int y, const char *string, const float *setColor, 
        qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars );
void CG_DrawBigString( int x, int y, const char *s, float alpha );
void CG_DrawBigStringColor( int x, int y, const char *s, vec4_t color );
void CG_DrawSmallString( int x, int y, const char *s, float alpha );
void CG_DrawSmallStringColor( int x, int y, const char *s, vec4_t color );

int CG_DrawStrlen( const char *str );

float	*CG_FadeColor( int startMsec, int totalMsec );
float *CG_TeamColor( int team );
void CG_TileClear( void );
void CG_ColorForHealth( vec4_t hcolor );
void CG_GetColorForHealth( int health, int armor, vec4_t hcolor );

void UI_DrawProportionalString( int x, int y, const char* str, int style, vec4_t color );
void CG_DrawRect( float x, float y, float width, float height, float size, const float *color );
void CG_DrawSides(float x, float y, float w, float h, float size);
void CG_DrawTopBottom(float x, float y, float w, float h, float size);


//
// cg_draw.c, cg_newDraw.c
//
extern	int sortedTeamPlayers[TEAM_MAXOVERLAY];
extern	int	numSortedTeamPlayers;
extern	int drawTeamOverlayModificationCount;
extern  char systemChat[256];
extern  char teamChat1[256];
extern  char teamChat2[256];

void CG_AddLagometerFrameInfo( void );
void CG_AddLagometerSnapshotInfo( snapshot_t *snap );
void CG_CenterPrint( const char *str, int y, int charWidth );
void CG_DrawHead( float x, float y, float w, float h, int clientNum, vec3_t headAngles );
void CG_DrawActive( stereoFrame_t stereoView );
void CG_DrawFlagModel( float x, float y, float w, float h, int team, qboolean force2D );
void CG_DrawTeamBackground( int x, int y, int w, int h, float alpha, int team );
void CG_OwnerDraw(float x, float y, float w, float h, float text_x, float text_y, int ownerDraw, int ownerDrawFlags, int align, float special, float scale, vec4_t color, qhandle_t shader, int textStyle);
void CG_Text_Paint(float x, float y, float scale, vec4_t color, const char *text, float adjust, int limit, int style);
int CG_Text_Width(const char *text, float scale, int limit);
int CG_Text_Height(const char *text, float scale, int limit);
void CG_SelectPrevPlayer( void );
void CG_SelectNextPlayer( void );
float CG_GetValue(int ownerDraw);
qboolean CG_OwnerDrawVisible(int flags);
void CG_RunMenuScript(char **args);
void CG_ShowResponseHead( void );
void CG_SetPrintString(int type, const char *p);
void CG_InitTeamChat( void );
void CG_GetTeamColor(vec4_t *color);
const char *CG_GetGameStatusText( void );
const char *CG_GetKillerText( void );
void CG_Draw3DModel(float x, float y, float w, float h, qhandle_t model, qhandle_t skin, vec3_t origin, vec3_t angles);
void CG_Text_PaintChar(float x, float y, float width, float height, float scale, float s, float t, float s2, float t2, qhandle_t hShader);
void CG_CheckOrderPending( void );
const char *CG_GameTypeString( void );
qboolean CG_YourTeamHasFlag( void );
qboolean CG_OtherTeamHasFlag( void );
qhandle_t CG_StatusHandle(int task);



//
// cg_player.c
//
void CG_Player( centity_t *cent );
void CG_ResetPlayerEntity( centity_t *cent );
void CG_AddRefEntityWithPowerups( refEntity_t *ent, entityState_t *state, int team, qboolean isMissile );
void CG_NewClientInfo( int clientNum );
sfxHandle_t	CG_CustomSound( int clientNum, const char *soundName );

//
// cg_predict.c
//
void CG_BuildSolidList( void );
int	CG_PointContents( const vec3_t point, int passEntityNum );
void CG_Trace( trace_t *result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, 
        int skipNumber, int mask );
void CG_PredictPlayerState( void );
void CG_LoadDeferredPlayers( void );


//
// cg_events.c
//
void CG_CheckEvents( centity_t *cent );
const char	*CG_PlaceString( int rank );
void CG_EntityEvent( centity_t *cent, vec3_t position );
void CG_PainEvent( centity_t *cent, int health );


//
// cg_ents.c
//
void CG_SetEntitySoundPosition( centity_t *cent );
void CG_AddPacketEntities( void );
void CG_Beam( centity_t *cent );
void CG_AdjustPositionForMover( const vec3_t in, int moverNum, int fromTime, int toTime, vec3_t out );

void CG_PositionEntityOnTag( refEntity_t *entity, const refEntity_t *parent, 
        qhandle_t parentModel, char *tagName );
void CG_PositionRotatedEntityOnTag( refEntity_t *entity, const refEntity_t *parent, 
        qhandle_t parentModel, char *tagName );



//
// cg_weapons.c
//
void CG_NextWeapon_f( void );
void CG_PrevWeapon_f( void );
void CG_Weapon_f( void );

void CG_RegisterWeapon( int weaponNum );
void CG_RegisterItemVisuals( int itemNum );

void CG_FireWeapon( centity_t *cent );
void CG_MissileHitWall( int weapon, int clientNum, vec3_t origin, vec3_t dir, impactSound_t soundType );
void CG_MissileHitPlayer( int weapon, vec3_t origin, vec3_t dir, int entityNum );
void CG_ShotgunFire( entityState_t *es );
void CG_Bullet( vec3_t origin, int sourceEntityNum, vec3_t normal, qboolean flesh, int fleshEntityNum );

void CG_RailTrail( clientInfo_t *ci, vec3_t start, vec3_t end );
void CG_GrappleTrail( centity_t *ent, const weaponInfo_t *wi );
void CG_AddViewWeapon (playerState_t *ps);
void CG_AddPlayerWeapon( refEntity_t *parent, playerState_t *ps, centity_t *cent, int team );
void CG_DrawWeaponSelect( void );

void CG_DrawWeaponBar0(int count, int bits);
void CG_DrawWeaponBar1(int count, int bits);
void CG_DrawWeaponBar2(int count, int bits, float *color);
void CG_DrawWeaponBar3(int count, int bits, float *color);
void CG_DrawWeaponBar4(int count, int bits, float *color);
void CG_DrawWeaponBar5(int count, int bits, float *color);
void CG_DrawWeaponBar6(int count, int bits, float *color);
void CG_DrawWeaponBar7(int count, int bits, float *color);

void CG_OutOfAmmoChange( void );	// should this be in pmove?

//
// cg_marks.c
//
void	CG_InitMarkPolys( void );
void	CG_AddMarks( void );
void	CG_ImpactMark( qhandle_t markShader, 
        const vec3_t origin, const vec3_t dir, 
        float orientation, 
        float r, float g, float b, float a, 
        qboolean alphaFade, 
        float radius, qboolean temporary );
void    CG_LeiSparks (vec3_t org, vec3_t vel, int duration, float x, float y, float speed);
void    CG_LeiSparks2 (vec3_t org, vec3_t vel, int duration, float x, float y, float speed);
void    CG_LeiPuff (vec3_t org, vec3_t vel, int duration, float x, float y, float speed, float size);


//
// cg_localents.c
//
void	CG_InitLocalEntities( void );
localEntity_t	*CG_AllocLocalEntity( void );
void	CG_AddLocalEntities( void );

//
// cg_effects.c
//
localEntity_t *CG_SmokePuff( const vec3_t p, 
        const vec3_t vel, 
        float radius,
        float r, float g, float b, float a,
        float duration,
        int startTime,
        int fadeInTime,
        int leFlags,
        qhandle_t hShader );
void CG_BubbleTrail( vec3_t start, vec3_t end, float spacing );
void CG_SpawnEffect( vec3_t org );
//#ifdef MISSIONPACK
void CG_KamikazeEffect( vec3_t org );
void CG_ObeliskExplode( vec3_t org, int entityNum );
void CG_ObeliskPain( vec3_t org );
void CG_InvulnerabilityImpact( vec3_t org, vec3_t angles );
void CG_InvulnerabilityJuiced( vec3_t org );
void CG_LightningBoltBeam( vec3_t start, vec3_t end );
//#endif
void CG_ScorePlum( int client, vec3_t org, int score );

void CG_GibPlayer( vec3_t playerOrigin );
void CG_BigExplode( vec3_t playerOrigin );

void CG_Bleed( vec3_t origin, int entityNum );

localEntity_t *CG_MakeExplosion( vec3_t origin, vec3_t dir,
        qhandle_t hModel, qhandle_t shader, int msec,
        qboolean isSprite );

void CG_SpurtBlood( vec3_t origin, vec3_t velocity, int hard );

//
// cg_snapshot.c
//
void CG_ProcessSnapshots( void );
//unlagged - early transitioning
void CG_TransitionEntity( centity_t *cent );
//unlagged - early transitioning

//
// cg_info.c
//
void CG_LoadingString( const char *s );
void CG_LoadingItem( int itemNum );
void CG_LoadingClient( int clientNum );
void CG_DrawInformation( void );

//
// cg_scoreboard.c
//
qboolean CG_DrawOldScoreboard( void );
void CG_DrawOldTourneyScoreboard( void );

//
// cg_challenges.c
//
void challenges_init(void);
void challenges_save(void);
unsigned int getChallenge(int challenge);
void addChallenge(int challenge);

//
// cg_consolecmds.c
//
qboolean CG_ConsoleCommand( void );
void CG_InitConsoleCommands( void );

//
// cg_servercmds.c
//
void CG_ExecuteNewServerCommands( int latestSequence );
void CG_ParseServerinfo( void );
void CG_SetConfigValues( void );
void CG_LoadVoiceChats( void );
void CG_ShaderStateChanged(void);
void CG_VoiceChatLocal( int mode, qboolean voiceOnly, int clientNum, int color, const char *cmd );
void CG_PlayBufferedVoiceChats( void );

//
// cg_playerstate.c
//
void CG_Respawn( void );
void CG_TransitionPlayerState( playerState_t *ps, playerState_t *ops );
void CG_CheckChangedPredictableEvents( playerState_t *ps );


//===============================================

//
// system traps
// These functions are how the cgame communicates with the main game system
//

// print message on the local console
void		trap_Print( const char *fmt );

// abort the game
void		trap_Error( const char *fmt )  __attribute__((noreturn));

// milliseconds should only be used for performance tuning, never
// for anything game related.  Get time from the CG_DrawActiveFrame parameter
int			trap_Milliseconds( void );

// console variable interaction
void		trap_Cvar_Register( vmCvar_t *vmCvar, const char *varName, const char *defaultValue, int flags );
void		trap_Cvar_Update( vmCvar_t *vmCvar );
void		trap_Cvar_Set( const char *var_name, const char *value );
void		trap_Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );

// ServerCommand and ConsoleCommand parameter access
int			trap_Argc( void );
void		trap_Argv( int n, char *buffer, int bufferLength );
void		trap_Args( char *buffer, int bufferLength );

// filesystem access
// returns length of file
int			trap_FS_FOpenFile( const char *qpath, fileHandle_t *f, fsMode_t mode );
void		trap_FS_Read( void *buffer, int len, fileHandle_t f );
void		trap_FS_Write( const void *buffer, int len, fileHandle_t f );
void		trap_FS_FCloseFile( fileHandle_t f );
int			trap_FS_Seek( fileHandle_t f, long offset, int origin ); // fsOrigin_t

// add commands to the local console as if they were typed in
// for map changing, etc.  The command is not executed immediately,
// but will be executed in order the next time console commands
// are processed
void		trap_SendConsoleCommand( const char *text );

// register a command name so the console can perform command completion.
// FIXME: replace this with a normal console command "defineCommand"?
void		trap_AddCommand( const char *cmdName );

// send a string to the server over the network
void		trap_SendClientCommand( const char *s );

// force a screen update, only used during gamestate load
void		trap_UpdateScreen( void );

// model collision
void		trap_CM_LoadMap( const char *mapname );
int			trap_CM_NumInlineModels( void );
clipHandle_t trap_CM_InlineModel( int index );		// 0 = world, 1+ = bmodels
clipHandle_t trap_CM_TempBoxModel( const vec3_t mins, const vec3_t maxs );
int			trap_CM_PointContents( const vec3_t p, clipHandle_t model );
int			trap_CM_TransformedPointContents( const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles );
void		trap_CM_BoxTrace( trace_t *results, const vec3_t start, const vec3_t end,
        const vec3_t mins, const vec3_t maxs,
        clipHandle_t model, int brushmask );
void		trap_CM_TransformedBoxTrace( trace_t *results, const vec3_t start, const vec3_t end,
        const vec3_t mins, const vec3_t maxs,
        clipHandle_t model, int brushmask,
        const vec3_t origin, const vec3_t angles );

// Returns the projection of a polygon onto the solid brushes in the world
int			trap_CM_MarkFragments( int numPoints, const vec3_t *points, 
        const vec3_t projection,
        int maxPoints, vec3_t pointBuffer,
        int maxFragments, markFragment_t *fragmentBuffer );

// normal sounds will have their volume dynamically changed as their entity
// moves and the listener moves
void		trap_S_StartSound( vec3_t origin, int entityNum, int entchannel, sfxHandle_t sfx );
void		trap_S_StopLoopingSound(int entnum);

// a local sound is always played full volume
void		trap_S_StartLocalSound( sfxHandle_t sfx, int channelNum );
void		trap_S_ClearLoopingSounds( qboolean killall );
void		trap_S_AddLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx );
void		trap_S_AddRealLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx );
void		trap_S_UpdateEntityPosition( int entityNum, const vec3_t origin );

// respatialize recalculates the volumes of sound as they should be heard by the
// given entityNum and position
void		trap_S_Respatialize( int entityNum, const vec3_t origin, vec3_t axis[3], int inwater );
sfxHandle_t	trap_S_RegisterSound( const char *sample, qboolean compressed );		// returns buzz if not found
void		trap_S_StartBackgroundTrack( const char *intro, const char *loop );	// empty name stops music
void	trap_S_StopBackgroundTrack( void );


void		trap_R_LoadWorldMap( const char *mapname );

// all media should be registered during level startup to prevent
// hitches during gameplay
qhandle_t	trap_R_RegisterModel( const char *name );			// returns rgb axis if not found
qhandle_t	trap_R_RegisterSkin( const char *name );			// returns all white if not found
qhandle_t	trap_R_RegisterShader( const char *name );			// returns all white if not found
qhandle_t	trap_R_RegisterShaderNoMip( const char *name );			// returns all white if not found

// a scene is built up by calls to R_ClearScene and the various R_Add functions.
// Nothing is drawn until R_RenderScene is called.
void		trap_R_ClearScene( void );
void		trap_R_AddRefEntityToScene( const refEntity_t *re );

// polys are intended for simple wall marks, not really for doing
// significant construction
void		trap_R_AddPolyToScene( qhandle_t hShader , int numVerts, const polyVert_t *verts );
void		trap_R_AddPolysToScene( qhandle_t hShader , int numVerts, const polyVert_t *verts, int numPolys );
void		trap_R_AddLightToScene( const vec3_t org, float intensity, float r, float g, float b );
int			trap_R_LightForPoint( vec3_t point, vec3_t ambientLight, vec3_t directedLight, vec3_t lightDir );
void		trap_R_RenderScene( const refdef_t *fd );
void		trap_R_SetColor( const float *rgba );	// NULL = 1,1,1,1
void		trap_R_DrawStretchPic( float x, float y, float w, float h, 
        float s1, float t1, float s2, float t2, qhandle_t hShader );
void		trap_R_ModelBounds( clipHandle_t model, vec3_t mins, vec3_t maxs );
int			trap_R_LerpTag( orientation_t *tag, clipHandle_t mod, int startFrame, int endFrame, 
        float frac, const char *tagName );
void		trap_R_RemapShader( const char *oldShader, const char *newShader, const char *timeOffset );

// The glconfig_t will not change during the life of a cgame.
// If it needs to change, the entire cgame will be restarted, because
// all the qhandle_t are then invalid.
void		trap_GetGlconfig( glconfig_t *glconfig );

// the gamestate should be grabbed at startup, and whenever a
// configstring changes
void		trap_GetGameState( gameState_t *gamestate );

// cgame will poll each frame to see if a newer snapshot has arrived
// that it is interested in.  The time is returned seperately so that
// snapshot latency can be calculated.
void		trap_GetCurrentSnapshotNumber( int *snapshotNumber, int *serverTime );

// a snapshot get can fail if the snapshot (or the entties it holds) is so
// old that it has fallen out of the client system queue
qboolean	trap_GetSnapshot( int snapshotNumber, snapshot_t *snapshot );

// retrieve a text command from the server stream
// the current snapshot will hold the number of the most recent command
// qfalse can be returned if the client system handled the command
// argc() / argv() can be used to examine the parameters of the command
qboolean	trap_GetServerCommand( int serverCommandNumber );

// returns the most recent command number that can be passed to GetUserCmd
// this will always be at least one higher than the number in the current
// snapshot, and it may be quite a few higher if it is a fast computer on
// a lagged connection
int			trap_GetCurrentCmdNumber( void );	

qboolean	trap_GetUserCmd( int cmdNumber, usercmd_t *ucmd );

// used for the weapon select and zoom
void		trap_SetUserCmdValue( int stateValue, float sensitivityScale );

// aids for VM testing
void		testPrintInt( char *string, int i );
void		testPrintFloat( char *string, float f );

int			trap_MemoryRemaining( void );
void		trap_R_RegisterFont(const char *fontName, int pointSize, fontInfo_t *font);
qboolean	trap_Key_IsDown( int keynum );
int			trap_Key_GetCatcher( void );
void		trap_Key_SetCatcher( int catcher );
int			trap_Key_GetKey( const char *binding );


typedef enum {
    SYSTEM_PRINT,
    CHAT_PRINT,
    TEAMCHAT_PRINT
} q3print_t; // bk001201 - warning: useless keyword or type name in empty declaration


int trap_CIN_PlayCinematic( const char *arg0, int xpos, int ypos, int width, int height, int bits);
e_status trap_CIN_StopCinematic(int handle);
e_status trap_CIN_RunCinematic (int handle);
void trap_CIN_DrawCinematic (int handle);
void trap_CIN_SetExtents (int handle, int x, int y, int w, int h);

void trap_SnapVector( float *v );

qboolean	trap_loadCamera(const char *name);
void		trap_startCamera(int time);
qboolean	trap_getCameraInfo(int time, vec3_t *origin, vec3_t *angles);

qboolean	trap_GetEntityToken( char *buffer, int bufferSize );

void	CG_ClearParticles (void);
void	CG_AddParticles (void);
void	CG_ParticleSnow (qhandle_t pshader, vec3_t origin, vec3_t origin2, int turb, float range, int snum);
void	CG_ParticleSmoke (qhandle_t pshader, centity_t *cent);
void	CG_AddParticleShrapnel (localEntity_t *le);
void	CG_ParticleSnowFlurry (qhandle_t pshader, centity_t *cent);
void	CG_ParticleBulletDebris (vec3_t	org, vec3_t vel, int duration);
void	CG_ParticleSparks (vec3_t org, vec3_t vel, int duration, float x, float y, float speed);
void	CG_ParticleDust (centity_t *cent, vec3_t origin, vec3_t dir);
void	CG_ParticleMisc (qhandle_t pshader, vec3_t origin, int size, int duration, float alpha);
void	CG_ParticleExplosion (char *animStr, vec3_t origin, vec3_t vel, int duration, int sizeStart, int sizeEnd);
extern qboolean		initparticles;
int CG_NewParticleArea ( int num );


// LEILEI ENHANCEMENT









#endif
