/*
     ZZZZZZZZZZZZZZZZZZZZ    8888888888888       00000000000
   ZZZZZZZZZZZZZZZZZZZZ    88888888888888888    0000000000000
                ZZZZZ      888           888  0000         0000
              ZZZZZ        88888888888888888  0000         0000
            ZZZZZ            8888888888888    0000         0000       AAAAAA         SSSSSSSSSSS   MMMM       MMMM
          ZZZZZ            88888888888888888  0000         0000      AAAAAAAA      SSSS            MMMMMM   MMMMMM
        ZZZZZ              8888         8888  0000         0000     AAAA  AAAA     SSSSSSSSSSS     MMMMMMMMMMMMMMM
      ZZZZZ                8888         8888  0000         0000    AAAAAAAAAAAA      SSSSSSSSSSS   MMMM MMMMM MMMM
    ZZZZZZZZZZZZZZZZZZZZZ  88888888888888888    0000000000000     AAAA      AAAA           SSSSS   MMMM       MMMM
  ZZZZZZZZZZZZZZZZZZZZZ      8888888888888       00000000000     AAAA        AAAA  SSSSSSSSSSS     MMMM       MMMM

Copyright (C) Gunther Strube, InterLogic 1993-99
*/

/* $Header: /home/dom/z88dk-git/cvs/z88dk/src/z80asm/Attic/prsident.c,v 1.25 2011-08-19 15:53:58 pauloscustodio Exp $ */
/* $Log: prsident.c,v $
/* Revision 1.25  2011-08-19 15:53:58  pauloscustodio
/* BUG_0010 : heap corruption when reaching MAXCODESIZE
/* - test for overflow of MAXCODESIZE is done before each instruction at parseline(); if only one byte is available in codearea, and a 2 byte instruction is assembled, the heap is corrupted before the exception is raised.
/* - Factored all the codearea-accessing code into a new module, checking for MAXCODESIZE on every write.
/*
/* Revision 1.24  2011/07/18 00:48:25  pauloscustodio
/* Initialize MS Visual Studio DEBUG build to show memory leaks on exit
/*
/* Revision 1.23  2011/07/12 22:47:59  pauloscustodio
/* - Moved all error variables and error reporting code to a separate module errors.c,
/*   replaced all extern declarations of these variables by include errors.h,
/*   created symbolic constants for error codes.
/* - Added test scripts for error messages.
/*
/* Revision 1.22  2011/07/11 16:02:04  pauloscustodio
/* Moved all option variables and option handling code to a separate module options.c,
/* replaced all extern declarations of these variables by include options.h.
/*
/* Revision 1.21  2011/07/09 18:25:35  pauloscustodio
/* Log keyword in checkin comment was expanded inside Log expansion... recursive
/* Added Z80asm banner to all source files
/*
/* Revision 1.20  2011/07/09 17:36:09  pauloscustodio
/* Copied cvs log into Log history
/*
/* Revision 1.19  2011/07/09 01:46:00  pauloscustodio
/* Added Log keyword
/* 
/* Revision 1.18  2011/07/09 01:21:55  pauloscustodio
/* added DefineSymbol() declaration
/* 
/* Revision 1.17  2011/02/27 11:58:46  stefano
/* Rolled back z80asm changes (I must have messed up something!!)
/* Slightly updated console output for Enterprise..
/* 
/* Revision 1.16  2011/02/23 16:27:39  stefano
/* *** empty log message ***
/* 
/* Revision 1.15  2010/09/19 00:06:20  dom
/* Tweaks for compiling code generated by sdcc - it generates XREF rather than
/* LIB so treat XREF as a LIB (this possibly should be the default)
/* 
/* Do some _ mapping magic when in sdcc so standard z88dk libs can be used
/* (wrong _ convention chosen a long time ago...)
/* 
/* Have -forcexlib flag which treats MODULE as XLIB.
/* 
/* Revision 1.14  2010/04/16 17:34:37  dom
/* Make line number an int - 32768 lines isn't big enough...
/* 
/* Revision 1.13  2009/10/11 00:24:38  dom
/* Define a symbol each time we come across a LINE directive - this will
/* assist the debugger somewhat
/* 
/* Revision 1.12  2009/07/18 23:23:15  dom
/* clean up the code a bit more (Formatting and a fewer magic numbers)
/* 
/* Revision 1.11  2009/05/28 20:33:58  dom
/* retn isn't available either on a rabbit
/* 
/* Revision 1.10  2009/05/28 19:20:16  dom
/* For the RCM SLL isn't a valid opcode, neither is anything using ixh,ixl,iyh
/* or iyl.
/* 
/* Revision 1.9  2009/05/28 18:49:54  dom
/* Some opcodes didn't come out right
/* 
/* Revision 1.8  2007/06/17 12:07:43  dom
/* Commit the rabbit emulation code including rrd, rld
/* 
/* Add a .vcproj for visual studio
/* 
/* Revision 1.7  2007/02/28 11:23:24  stefano
/* New platform !
/* Rabbit Control Module 2000/3000.
/* 
/* Revision 1.6  2003/10/11 15:41:04  dom
/* changes from garry
/* 
/* - support for defp -> defp addr,bank
/* - square brackets can be used in expressions
/* - comma can be used in defm
/* 
/* Revision 1.5  2002/05/11 20:09:38  dom
/* A patch around the appalling IF ELSE ENDIF handling of z80asm where it
/* tries to evaluate FALSE clauses and gets completely in a twist.
/* 
/* These patches turn off the output to the two errors that I've seen pop
/* up in this state: Syntax error and unknown identifier. Please test this
/* one quite hard if you get a change... - it was done to allow even more
/* complicated logic in the z88 app startup to actually work - as soon as I'm
/* happy with that I'll commit it as well
/* 
/* Revision 1.4  2001/02/28 18:19:24  dom
/* Fixed size of Z80ident table <grrr>
/* 
/* Revision 1.3  2001/02/28 17:59:22  dom
/* Added UNDEFINE for undefining symbols, bumped version to 1.0.18
/* 
/* Revision 1.2  2001/01/23 10:00:09  dom
/* Changes by x1cygnus:
/* 
/* just added a harcoded macro Invoke, similar to callpkg except that the
/* instruction 'Invoke' resolves to a call by default (ti83) and to a RST if
/* the parameter -plus is specified on the command line.
/* 
/* Changes by dom:
/* Added in a rudimentary default directory set up (Defined at compile time)
/* a bit kludgy and not very nice!
/* 
/* Revision 1.1  2000/07/04 15:33:30  dom
/* branches:  1.1.1;
/* Initial revision
/* 
/* Revision 1.1.1.1  2000/07/04 15:33:30  dom
/* First import of z88dk into the sourceforge system <gulp>
/* 
/* */

/* $History: PRSIDENT.C $ */
/*  */
/* *****************  Version 14  ***************** */
/* User: Gbs          Date: 30-01-00   Time: 12:51 */
/* Updated in $/Z80asm */
/* Bug fix from v1.0.14 where IF, ELSE & ENDIF id's were wrong in  */
/* ParseIdent () due to new CALL_PKG pseudo macro. */
/*  */
/* *****************  Version 13  ***************** */
/* User: Gbs          Date: 30-09-99   Time: 22:39 */
/* Updated in $/Z80asm */
/* CALL_PKG hard coded macro implemented for Garry Lancaster's Package */
/* System. */
/*  */
/* *****************  Version 11  ***************** */
/* User: Gbs          Date: 6-06-99    Time: 20:06 */
/* Updated in $/Z80asm */
/* "PC" program counter changed to long (from unsigned short). */
/*  */
/* *****************  Version 9  ***************** */
/* User: Gbs          Date: 6-06-99    Time: 12:13 */
/* Updated in $/Z80asm */
/* Added Ascii Art "Z80asm" at top of source file. */
/*  */
/* *****************  Version 7  ***************** */
/* User: Gbs          Date: 6-06-99    Time: 11:30 */
/* Updated in $/Z80asm */
/* "config.h" included before "symbol.h" */
/*  */
/* *****************  Version 5  ***************** */
/* User: Gbs          Date: 17-04-99   Time: 0:30 */
/* Updated in $/Z80asm */
/* New GNU programming style C format. Improved ANSI C coding style */
/* eliminating previous compiler warnings. New -o option. Asm sources file */
/* now parsed even though any line feed standards (CR,LF or CRLF) are */
/* used. */
/*  */
/* *****************  Version 4  ***************** */
/* User: Gbs          Date: 7-03-99    Time: 13:13 */
/* Updated in $/Z80asm */
/* Minor changes to keep C compiler happy. */
/*  */
/* *****************  Version 2  ***************** */
/* User: Gbs          Date: 20-06-98   Time: 15:04 */
/* Updated in $/Z80asm */
/* SUB, AND, OR, XOR and CP instruction improved with alternative syntax: */
/* "<instr> [A,]xxx", allowing for specification of accumulator. This */
/* makes all accumulator related instructions equal in syntax and removes */
/* ambiguity. */

#include "memalloc.h"	/* before any other include to enable memory leak detection */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "z80asm.h"
#include "symbol.h"
#include "options.h"
#include "errors.h"
#include "codearea.h"

/* external functions */
void Skipline (FILE *fptr);
int DefineSymbol (char *identifier, long value, unsigned char symboltype);
void Subroutine_addr (int opc0, int opc);
void JP_instr (int opc0, int opc);
void PushPop_instr (int opcode);
void RotShift_instr (int opcode);
void BitTest_instr (int opcode);
void ArithLog8_instr (int opcode);
void DeclSymGlobal (char *identifier, unsigned char libtype);
void DeclSymExtern (char *identifier, unsigned char libtype);
void DeclModuleName (void);
void DefSym (void);
void ifstatement (enum flag interpret);
void DEFVARS (void), DEFS (void), ORG (void), IncludeFile (void), BINARY (void), CALLOZ (void), CALLPKG (void), FPP (void);
void ADC (void), ADD (void), DEC (void), IM (void), IN (void), INC (void), INVOKE (void);
void JR (void), LD (void), OUT (void), RET (void), SBC (void);
void DEFB (void), DEFC (void), DEFM (void), DEFW (void), DEFL (void), DEFP (void);
void RST (void), DEFGROUP (void);
long GetConstant(char *);
int CheckRegister8 (void);
void UnDefineSym(void);


/* local functions */
void ParseIdent (enum flag interpret);
void AND (void), BIT (void), CALL (void), CCF (void), CP (void), CPD (void);
void CPDR (void), CPI (void), CPIR (void), CPL (void), DAA (void);
void DI (void), DJNZ (void);
void EI (void), EX (void), EXX (void), HALT (void);
void IND (void);
void INDR (void), INI (void), INIR (void), JP (void);
void LDD (void), LDDR (void);
void LDI (void), LDIR (void), NEG (void), NOP (void), OR (void), OTDR (void), OTIR (void);
void OUTD (void), OUTI (void), POP (void), PUSH (void), RES (void);
void RETI (void), RETN (void);
void RL (void), RLA (void), RLC (void), RLCA (void), RLD (void), RR (void), RRA (void), RRC (void);
void RRCA (void), RRD (void);
void SCF (void), SET (void), SLA (void), SLL (void), SRA (void);
void SRL (void), SUB (void), XOR (void);
void DeclExternIdent (void), DeclGlobalIdent (void), ListingOn (void), ListingOff (void);
void DeclLibIdent (void), DeclGlobalLibIdent (void);
void IFstat (void), ELSEstat (void), ENDIFstat (void);
void DeclModule (void);
void LINE (void);
void SetTemporaryLine(char *line);

/* global variables */
extern FILE *z80asmfile;
extern enum symbols sym, GetSym (void);
extern enum flag writeline, EOL;
extern char ident[], line[];
extern struct module *CURRENTMODULE;


typedef void (*ptrfunc) (void);	/* ptr to function returning void */
typedef int (*fptr) (const void *, const void *);

struct Z80sym
  {
    char *z80mnem;
    ptrfunc z80func;
  };


struct Z80sym Z80ident[] = {
 {"ADC", ADC},			/* 0 */
 {"ADD", ADD},
 {"AND", AND},
 {"BINARY", BINARY},
 {"BIT", BIT},
 {"CALL", CALL},		/* 5 */
 {"CALL_OZ", CALLOZ},
 {"CALL_PKG", CALLPKG},
 {"CCF", CCF},
 {"CP", CP},
 {"CPD", CPD},			/* 10 */
 {"CPDR", CPDR},		
 {"CPI", CPI},
 {"CPIR", CPIR},
 {"CPL", CPL},
 {"DAA", DAA},			/* 15 */
 {"DEC", DEC},			
 {"DEFB", DEFB},
 {"DEFC", DEFC},
 {"DEFGROUP", DEFGROUP},
 {"DEFINE", DefSym},		/* 20 */
 {"DEFL", DEFL},		
 {"DEFM", DEFM},
 {"DEFP", DEFP},
 {"DEFS", DEFS},
 {"DEFVARS", DEFVARS},		/* 25 */
 {"DEFW", DEFW},
 {"DI", DI},			
 {"DJNZ", DJNZ},
 {"EI", EI},
 {"ELSE", ELSEstat},		/* 30 */
 {"ENDIF", ENDIFstat},	
 {"EX", EX},			
 {"EXX", EXX},
 {"FPP", FPP},
 {"HALT", HALT},		/* 35 */
 {"IF", IFstat},
 {"IM", IM},			
 {"IN", IN},
 {"INC", INC},
 {"INCLUDE", IncludeFile},	/* 40 */
 {"IND", IND},
 {"INDR", INDR},
 {"INI", INI},
 {"INIR", INIR},
 {"INVOKE", INVOKE},		/* 45 */
 {"JP", JP},
 {"JR", JR},
 {"LD", LD},
 {"LDD", LDD},
 {"LDDR", LDDR},		/* 50 */
 {"LDI", LDI},
 {"LDIR", LDIR},
 {"LIB", DeclLibIdent},
 {"LINE", LINE},
 {"LSTOFF", ListingOff},	/* 55 */
 {"LSTON", ListingOn},
 {"MODULE", DeclModule},
 {"NEG", NEG},
 {"NOP", NOP},
 {"OR", OR},			/* 60 */
 {"ORG", ORG},
 {"OTDR", OTDR},
 {"OTIR", OTIR},
 {"OUT", OUT},
 {"OUTD", OUTD},		/* 65 */
 {"OUTI", OUTI},
 {"OZ", CALLOZ},		
 {"POP", POP},
 {"PUSH", PUSH},
 {"RES", RES},			/* 70 */
 {"RET", RET},
 {"RETI", RETI},
 {"RETN", RETN},
 {"RL", RL},
 {"RLA", RLA},			/* 75 */
 {"RLC", RLC},
 {"RLCA", RLCA},
 {"RLD", RLD},
 {"RR", RR},
 {"RRA", RRA},			/* 80 */
 {"RRC", RRC},
 {"RRCA", RRCA},
 {"RRD", RRD},
 {"RST", RST},
 {"SBC", SBC},			/* 85 */
 {"SCF", SCF},
 {"SET", SET},
 {"SLA", SLA},
 {"SLL", SLL},
 {"SRA", SRA},			/* 90 */
 {"SRL", SRL},
 {"SUB", SUB},
 {"UNDEFINE",UnDefineSym},
 {"XDEF", DeclGlobalIdent},
 {"XLIB", DeclGlobalLibIdent},	/* 95 */
 {"XOR", XOR},
 {"XREF", DeclExternIdent}
};

size_t totalz80id = sizeof(Z80ident) / sizeof(Z80ident[0]);


int 
idcmp (const char *idptr, const struct Z80sym *symptr)
{
  return strcmp (idptr, symptr->z80mnem);
}


int 
SearchId (void)
{
  struct Z80sym *foundsym;

  foundsym = (struct Z80sym *) bsearch (ident, Z80ident, totalz80id, sizeof (struct Z80sym), (fptr) idcmp);

  if (foundsym == NULL)
    return -1;
  else
    return foundsym - Z80ident;
}



void 
ParseIdent (enum flag interpret)
{
  int id;

  if ((id = SearchId ()) == -1 && interpret == ON) {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_UNKNOWN_IDENT);
  } else
    {
      switch (id)
	{
	case 36:		/* IF */
	  if (interpret == OFF)
	    Skipline (z80asmfile);	/* skip current line until EOL */
	  ifstatement (interpret);
	  break;

	case 30:		/* ELSE */
	case 31:		/* ENDIF */
	  (Z80ident[id].z80func) ();	
	  Skipline (z80asmfile);
	  break;

	default:
	  if (interpret == ON)
            {
	      (Z80ident[id].z80func) ();
            }
	  Skipline (z80asmfile);		/* skip current line until EOL */
	}
    }
}



void 
ListingOn (void)
{
  if (listing_CPY == ON)
    {
      listing = ON;		/* switch listing ON again... */
      writeline = OFF;		/* but don't write this line in listing file */
      line[0] = '\0';
    }
}



void 
ListingOff (void)
{
  if (listing_CPY == ON)
    {
      listing = writeline = OFF;	/* but don't write this line in listing file */
      line[0] = '\0';
    }
}

/* Function for Line number in C source */

void LINE(void)
{
	char	err;
        char    name[128];
	GetSym();
	clineno=GetConstant(&err);
	line[0]='\0';
        snprintf(name, sizeof(name),"__C_LINE_%d",clineno);
        DefineSymbol (name, get_PC(), SYMADDR | SYMTOUCHED);
}



/* dummy function - not used */
void 
IFstat (void)
{
}




void 
ELSEstat (void)
{
  sym = elsestatm;
  writeline = OFF;		/* but don't write this line in listing file */
}




void 
ENDIFstat (void)
{
  sym = endifstatm;
  writeline = OFF;		/* but don't write this line in listing file */
}



void 
DeclGlobalIdent (void)
{
  do
    {
      if (GetSym () == name)
	DeclSymGlobal (ident, 0);
      else
	{
	  ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_SYNTAX);
	  return;
	}
    }
  while (GetSym () == comma);

  if (sym != newline)
    ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_SYNTAX);
}



void 
DeclGlobalLibIdent (void)
{
  if (GetSym () == name)
    {
      DeclModuleName ();	/* XLIB name is implicit MODULE name */
      DeclSymGlobal (ident, SYMDEF);
    }
  else
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_SYNTAX);
      return;
    }
}



void 
DeclExternIdent (void)
{
  if ( sdcc_hacks == ON ) 
    {
      DeclLibIdent();
      return;
    }
  do
    {
      if (GetSym () == name)
	DeclSymExtern (ident, 0);	/* Define symbol as extern */
      else
	{
	  ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_SYNTAX);
	  return;
	}
    }
  while (GetSym () == comma);

  if (sym != newline)
    ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_SYNTAX);
}



void 
DeclLibIdent (void)
{

    do
    {
        if (GetSym () == name) {
            DeclSymExtern (ident, SYMDEF);	/* Define symbol as extern LIB reference */
        }
        else
        {
            ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_SYNTAX);
            return;
        }
    }
    while (GetSym () == comma);

    if (sym != newline)
        ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_SYNTAX);
}



void 
DeclModule (void)
{
  if ( force_xlib == ON )
    {
      DeclGlobalLibIdent();
    }
  else
    {
      GetSym ();
      DeclModuleName ();
    }
}


void 
NOP (void)
{
  append_byte(0x00);
  inc_PC(1);
}



void 
HALT (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0x76);
  inc_PC(1);
}



void 
LDI (void)
{
  append_byte(0xED);
  append_byte(0xA0);
  inc_PC(2);
}



void 
LDIR (void)
{
  append_byte(0xED);
  append_byte(0xB0);
  inc_PC(2);
}



void 
LDD (void)
{
  append_byte(0xED);
  append_byte(0xA8);
  inc_PC(2);
}



void 
LDDR (void)
{
  append_byte(0xED);
  append_byte(0xB8);
  inc_PC(2);
}



void 
CPI (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      SetTemporaryLine("\ncall rcmx_cpi\n");
      return;
    }

  append_byte(0xED);
  append_byte(0xA1);
  inc_PC(2);
}



void 
CPIR (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      SetTemporaryLine("\ncall rcmx_cpir\n");
      return;
    }

  append_byte(0xED);
  append_byte(0xB1);
  inc_PC(2);
}



void 
CPD (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      SetTemporaryLine("\ncall rcmx_cpd\n");
      return;
    }

  append_byte(0xED);
  append_byte(0xA9);
  inc_PC(2);
}



void 
CPDR (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      SetTemporaryLine("\ncall rcmx_cpdr\n");
      return;
    }

  append_byte(0xED);
  append_byte(0xB9);
  inc_PC(2);
}



void 
IND (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0xED);
  append_byte(0xAA);
  inc_PC(2);
}



void 
INDR (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0xED);
  append_byte(0xBA);
  inc_PC(2);
}



void 
INI (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }
  append_byte(0xED);
  append_byte(0xA2);
  inc_PC(2);
}



void 
INIR (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0xED);
  append_byte(0xB2);
  inc_PC(2);
}



void 
OUTI (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0xED);
  append_byte(0xA3);
  inc_PC(2);
}



void 
OUTD (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0xED);
  append_byte(0xAB);
  inc_PC(2);
}



void 
OTIR (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0xED);
  append_byte(0xB3);
  inc_PC(2);
}



void 
OTDR (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0xED);
  append_byte(0xBB);
  inc_PC(2);
}




/*
 * Allow specification of "<instr> [A,]xxx"
 * in SUB, AND, OR, XOR, CP instructions
 */
void 
ExtAccumulator (int opcode)
{
  long fptr;

  fptr = ftell (z80asmfile);

  if (GetSym () == name)
    {
      if (CheckRegister8 () == 7)
	{
	  if (GetSym () == comma)
	    {
	      /* <instr> A, ... */
	      ArithLog8_instr (opcode);

	      return;
	    }
	}
    }

  /* reparse and code generate (if possible) */
  sym = nil;
  EOL = OFF;

  fseek (z80asmfile, fptr, SEEK_SET);
  ArithLog8_instr (opcode);
}



void 
CP (void)
{
  ExtAccumulator (7);
}




void 
AND (void)
{
  ExtAccumulator (4);
}



void 
OR (void)
{
  ExtAccumulator (6);
}



void 
XOR (void)
{
  ExtAccumulator (5);
}


void 
SUB (void)
{
  ExtAccumulator (2);
}




void 
SET (void)
{
  BitTest_instr (192);
}



void 
RES (void)
{
  BitTest_instr (128);
}



void 
BIT (void)
{
  BitTest_instr (64);
}



void 
RLC (void)
{
  RotShift_instr (0);
}



void 
RRC (void)
{
  RotShift_instr (1);
}



void 
RL (void)
{
  RotShift_instr (2);
}



void 
RR (void)
{
  RotShift_instr (3);
}



void 
SLA (void)
{
  RotShift_instr (4);
}



void 
SRA (void)
{
  RotShift_instr (5);
}



void 
SLL (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }
  RotShift_instr (6);
}



void 
SRL (void)
{
  RotShift_instr (7);
}



void 
CPL (void)
{
  append_byte(0x2F);
  inc_PC(1);
}



void 
RLA (void)
{
  append_byte(0x17);
  inc_PC(1);
}



void 
RRA (void)
{
  append_byte(0x1F);
  inc_PC(1);
}



void 
RRCA (void)
{
  append_byte(0x0F);
  inc_PC(1);
}



void 
RLCA (void)
{
  append_byte(0x07);
  inc_PC(1);
}



void 
EXX (void)
{
  append_byte(0xD9);
  inc_PC(1);
}



void 
PUSH (void)
{
  PushPop_instr (197);
}



void 
POP (void)
{
  PushPop_instr (193);
}




void 
RETI (void)
{
  append_byte(0xED);
  append_byte(0x4D);
  inc_PC(2);
}



void 
RETN (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }
  append_byte(0xED);
  append_byte(0x45);
  inc_PC(2);
}



void 
RLD (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      SetTemporaryLine("\ncall rcmx_rld\n");
      return;
    }

  append_byte(0xED);
  append_byte(0x6F);
  inc_PC(2);
}



void 
RRD (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      SetTemporaryLine("\ncall rcmx_rrd\n");
      return;
    }

  append_byte(0xED);
  append_byte(0x67);
  inc_PC(2);
}



void 
NEG (void)
{
  append_byte(0xED);
  append_byte(0x44);
  inc_PC(2);
}



void 
CALL (void)
{
    Subroutine_addr (205, 196);
}



void 
JP (void)
{
  JP_instr (195, 194);
}



void 
CCF (void)
{
  append_byte(0x3F);
  inc_PC(1);
}



void 
SCF (void)
{
  append_byte(0x37);
  inc_PC(1);
}



void 
DI (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0xF3);
  inc_PC(1);
}



void 
EI (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0xFB);
  inc_PC(1);
}



void 
DAA (void)
{
  if ( (cpu_type & CPU_RABBIT) )
    {
      ReportError (CURRENTFILE->fname, CURRENTFILE->line, ERR_ILLEGAL_IDENT);
      return;
    }

  append_byte(0x27);
  inc_PC(1);
}

/*
 * Local Variables:
 *  indent-tabs-mode:nil
 *  require-final-newline:t
 *  c-basic-offset: 2
 *  eval: (c-set-offset 'case-label 0)
 *  eval: (c-set-offset 'substatement-open 2)
 *  eval: (c-set-offset 'access-label 0)
 *  eval: (c-set-offset 'class-open 2)
 *  eval: (c-set-offset 'class-close 2)
 * End:
 */


