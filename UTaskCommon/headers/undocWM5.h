#ifndef UNDOCWM5_H
#define UNDOCWM5_H
// INCOMPLETE!!! Process and some other structures are not fixed

typedef ulong PHYSICAL_ADDRESS;
#define INVALID_PHYSICAL_ADDRESS 0xFFFFFFFF
#define MAX_PROCESSES 32
#define PRIORITY_LEVELS_HASHSIZE 32

typedef void (*PKINTERRUPT_ROUTINE)(void);
#define IN
#define OUT
#define OPTIONAL

typedef void (*RETADDR)();

typedef struct Thread THREAD;
typedef THREAD *PTHREAD;

typedef struct Process PROCESS;
typedef PROCESS *PPROCESS;

typedef ulong ACCESSKEY;
typedef ulong ACCESSLOCK;

typedef struct Module MODULE;
typedef MODULE *PMODULE, *LPMODULE;

typedef RETADDR FNDISP(PTHREAD pth, RETADDR ra, void *args);
typedef FNDISP *PFNDISP;
typedef BOOL (*PFNKDBG)(DWORD dwCause, PTHREAD pictx);

typedef struct TOCentry {           // MODULE BIB section structure
    DWORD dwFileAttributes;
    FILETIME ftTime;
    DWORD nFileSize;
    LPSTR   lpszFileName;
    ULONG   ulE32Offset;            // Offset to E32 structure
    ULONG   ulO32Offset;            // Offset to O32 structure
    ULONG   ulLoadOffset;           // MODULE load buffer offset
} TOCentry, *LPTOCentry;

typedef wchar_t Name;
typedef Name* LPName;
typedef void* LPPROXY;
typedef void* PGPOOL_Q;
typedef struct cinfo CINFO;

/*
#define PM_NOPAGING 0
#define PM_FULLPAGING 1
#define PM_NOPAGEOUT 2

#define FT_OBJSTORE 2
#define FT_ROMIMAGE 3
#define FT_EXTIMAGE 4*/

typedef struct openexe_t {
    union {
        int hppfs;          // ppfs handle
        HANDLE hf;          // object store handle
        TOCentry *tocptr;   // rom entry pointer
    };
    BYTE filetype;
    BYTE bIsOID;
    WORD pagemode;
    union {
        DWORD offset;
        DWORD dwExtRomAttrib;
    };
    union {
        Name *lpName;
        CEOID ceOid;
    };
} openexe_t;

/* Internal reduced form of e32 header */

#define STD_EXTRA       16

#define EXP             0           /* Export table position               */
#define IMP             1           /* Import table position               */
#define RES             2           /* Resource table position             */
#define EXC             3           /* Exception table position            */
#define SEC             4           /* Security table position             */
#define FIX             5           /* Fixup table position                */
#define DEB             6           /* Debug table position                */
#define IMD             7           /* Image description table position    */
#define MSP             8           /* Machine specific table position     */
#define TLS             9           /* Thread Local Storage                */
#define CBK            10           /* Callbacks                           */
#define RS1            11           /* Reserved                            */
#define RS2            12           /* Reserved                            */
#define RS3            13           /* Reserved                            */
#define RS4            14           /* Reserved                            */
#define RS5            15           /* Reserved                            */

#define LITE_EXTRA      7           /* Only first 7 used by NK */

struct info {                       /* Extra information header block      */
    unsigned long   rva;            /* Virtual relative address of info    */
    unsigned long   size;           /* Size of information block           */
};

typedef struct e32_exe {            /* PE 32-bit .EXE header               */
    unsigned char   e32_magic[4];   /* Magic number E32_MAGIC              */
    unsigned short  e32_cpu;        /* The CPU type                        */
    unsigned short  e32_objcnt;     /* Number of memory objects            */
    unsigned long   e32_timestamp;  /* Time EXE file was created/modified  */
    unsigned long   e32_symtaboff;  /* Offset to the symbol table          */
    unsigned long   e32_symcount;   /* Number of symbols                   */
    unsigned short  e32_opthdrsize; /* Optional header size                */
    unsigned short  e32_imageflags; /* Image flags                         */
    unsigned short  e32_coffmagic;  /* Coff magic number (usually 0x10b)   */
    unsigned char   e32_linkmajor;  /* The linker major version number     */
    unsigned char   e32_linkminor;  /* The linker minor version number     */
    unsigned long   e32_codesize;   /* Sum of sizes of all code sections   */
    unsigned long   e32_initdsize;  /* Sum of all initialized data size    */
    unsigned long   e32_uninitdsize;/* Sum of all uninitialized data size  */
    unsigned long   e32_entryrva;   /* Relative virt. addr. of entry point */
    unsigned long   e32_codebase;   /* Address of beginning of code section*/
    unsigned long   e32_database;   /* Address of beginning of data section*/
    unsigned long   e32_vbase;      /* Virtual base address of module      */
    unsigned long   e32_objalign;   /* Object Virtual Address align. factor*/
    unsigned long   e32_filealign;  /* Image page alignment/truncate factor*/
    unsigned short  e32_osmajor;    /* The operating system major ver. no. */
    unsigned short  e32_osminor;    /* The operating system minor ver. no. */
    unsigned short  e32_usermajor;  /* The user major version number       */
    unsigned short  e32_userminor;  /* The user minor version number       */
    unsigned short  e32_subsysmajor;/* The subsystem major version number  */
    unsigned short  e32_subsysminor;/* The subsystem minor version number  */
    unsigned long   e32_res1;       /* Reserved bytes - must be 0  */
    unsigned long   e32_vsize;      /* Virtual size of the entire image    */
    unsigned long   e32_hdrsize;    /* Header information size             */
    unsigned long   e32_filechksum; /* Checksum for entire file            */
    unsigned short  e32_subsys;     /* The subsystem type                  */
    unsigned short  e32_dllflags;   /* DLL flags                           */
    unsigned long   e32_stackmax;   /* Maximum stack size                  */
    unsigned long   e32_stackinit;  /* Initial committed stack size        */
    unsigned long   e32_heapmax;    /* Maximum heap size                   */
    unsigned long   e32_heapinit;   /* Initial committed heap size         */
    unsigned long   e32_res2;       /* Reserved bytes - must be 0  */
    unsigned long   e32_hdrextra;   /* Number of extra info units in header*/
    struct info     e32_unit[STD_EXTRA]; /* Array of extra info units      */
} e32_exe, *LPe32_exe;

/* Internal reduced form of e32 header */

typedef struct e32_lite {           /* PE 32-bit .EXE header               */
    unsigned short  e32_objcnt;     /* Number of memory objects            */
    BYTE            e32_cevermajor; /* version of CE built for             */
    BYTE            e32_ceverminor; /* version of CE built for             */
    unsigned long   e32_stackmax;   /* Maximum stack size                  */
    unsigned long   e32_vbase;      /* Virtual base address of module      */
    unsigned long   e32_vsize;      /* Virtual size of the entire image    */
    unsigned long	e32_sect14rva;  /* section 14 rva */
    unsigned long	e32_sect14size; /* section 14 size */
    unsigned long   e32_timestamp;  /* Time EXE/DLL was created/modified   */
    struct info     e32_unit[LITE_EXTRA]; /* Array of extra info units     */
} e32_lite, *LPe32_list;

/*
 *  OBJECT TABLE
 */

#define E32OBJNAMEBYTES 8               /* Name bytes                       */

typedef struct o32_obj {                /* .EXE memory object table entry   */
    unsigned char       o32_name[E32OBJNAMEBYTES];/* Object name            */
    unsigned long       o32_vsize;      /* Virtual memory size              */
    unsigned long       o32_rva;        /* Object relative virtual address  */
    unsigned long       o32_psize;      /* Physical file size of init. data */
    unsigned long       o32_dataptr;    /* Image pages offset               */
    unsigned long       o32_realaddr;   /* pointer to actual                */
    unsigned long       o32_access;     /* assigned access                  */
    unsigned long       o32_temp3;
    unsigned long       o32_flags;      /* Attribute flags for the object   */
} o32_obj, *LPo32_obj;

typedef struct o32_lite {
    unsigned long       o32_vsize;
    unsigned long       o32_rva;
    unsigned long       o32_realaddr;
    unsigned long       o32_access;
    unsigned long       o32_flags;
    unsigned long       o32_psize;
    unsigned long       o32_dataptr;
} o32_lite, *LPo32_lite;

typedef void * PMODULELIST;

#include <pshpack1.h>
// Any time this structure is redefined, we need to recalculate
// the offset used in the SHx profiler ISR located at
// %_WINCEROOT%\platform\ODO\kernel\profiler\shx\profisr.src
struct Process {
    BYTE        procnum;        /* 00: ID of this process [ie: it's slot number] */
    BYTE        DbgActive;      /* 01: ID of process currently DebugActiveProcess'ing this process */
    BYTE        bChainDebug;    /* 02: Did the creator want to debug child processes? */
    BYTE        bTrustLevel;    /* 03: level of trust of this exe */
#define OFFSET_TRUSTLVL     3   // offset of the bTrustLevel member in Process structure
    LPPROXY     pProxList;      /* 04: list of proxies to threads blocked on this process */
    HANDLE      hProc;          /* 08: handle for this process, needed only for SC_GetProcFromPtr */
    DWORD       dwVMBase;       /* 0C: base of process's memory section, or 0 if not in use */
    PTHREAD     pTh;            /* 10: first thread in this process */
    ACCESSKEY   aky;            /* 14: default address space key for process's threads */
    LPVOID      BasePtr;        /* 18: Base pointer of exe load */
    HANDLE      hDbgrThrd;      /* 1C: handle of thread debugging this process, if any */
    LPWSTR      lpszProcName;   /* 20: name of process */
    DWORD       tlsLowUsed;     /* 24: TLS in use bitmask (first 32 slots) */
    DWORD       tlsHighUsed;    /* 28: TLS in use bitmask (second 32 slots) */
    PEXCEPTION_ROUTINE pfnEH;   /* 2C: process exception handler */
    LPDBGPARAM  ZonePtr;        /* 30: Debug zone pointer */
    PTHREAD     pMainTh;        /* 34  primary thread in this process*/
    PMODULE     pmodResource;   /* 38: module that contains the resources */
    LPName      pStdNames[3];   /* 3C: Pointer to names for stdio */
    LPCWSTR     pcmdline;       /* 48: Pointer to command line */
    DWORD       dwDyingThreads; /* 4C: number of pending dying threads */
    openexe_t   oe;             /* 50: Pointer to executable file handle */
    e32_lite    e32;            /* ??: structure containing exe header */
    o32_lite    *o32_ptr;       /* ??: o32 array pointer for exe */
    LPVOID      pExtPdata;      /* ??: extend pdata */
    BYTE        bPrio;          /* ??: highest priority of all threads of the process */
    BYTE        fNoDebug;       /* ??: this process cannot be debugged */
    WORD        wModCount;      /* ??: # of modules in pLastModList */
    PGPOOL_Q    pgqueue;        /* ??: list of the page owned by the process */
    PMODULELIST pLastModList;   /* ??: the list of modules that just loaded/unloaded into the process */
    HANDLE      hTok;           /* ??: process default token */
#if HARDWARE_PT_PER_PROC
    ulong       pPTBL[HARDWARE_PT_PER_PROC];   /* hardware page tables */
#endif
    LPVOID      pShimInfo;      /* pointer to shim information */
};  /* Process */
#include <poppack.h>

// REFINFO - reference info for Handle Data.
typedef struct FULLREF {
    ushort  usRefs[MAX_PROCESSES];
} FULLREF;
typedef union REFINFO {
    ulong   count;
    FULLREF *pFr;
} REFINFO;

// DList - double linked list
//
// WARNING: The double list routine are NOT preemtion safe. The list must
// be protected with a critical section or the functions should be invoked
// via KCall().

typedef struct _DList DList;
struct _DList {
    DList *fwd;
    DList *back;
};

// HDATA - handle data structure
typedef struct _HDATA HDATA, *PHDATA;
struct _HDATA {
    DList       linkage;    /* 00: links for active handle list */
    HANDLE      hValue;     /* 08: Current value of handle (nonce) */
    ACCESSLOCK  lock;       /* 0C: access information */
    REFINFO     ref;        /* 10: reference information */
    const CINFO *pci;       /* 14: ptr to object class description structure */
    PVOID       pvObj;      /* 18: ptr to object */
    DWORD       dwInfo;     /* 1C: extra handle info */
};                          /* 20: sizeof(HDATA) */

typedef struct PDATA {
    ULONG pFuncStart;
    ULONG PrologLen : 8;        // low order bits
    ULONG FuncLen   : 22;       // high order bits
    ULONG ThirtyTwoBits : 1;    // 0/1 == 16/32 bit instructions
    ULONG ExceptionFlag : 1;    // highest bit
} PDATA, *PPDATA;

typedef struct PDATA_EH {
    PEXCEPTION_ROUTINE pHandler;
    PVOID pHandlerData;
} PDATA_EH, *PPDATA_EH;

typedef struct Module {
    LPVOID      lpSelf;                 /* Self pointer for validation */
    PMODULE     pMod;                   /* Next module in chain */
    LPWSTR      lpszModName;            /* Module name */
    DWORD       inuse;                  /* Bit vector of use */
    WORD        refcnt[MAX_PROCESSES];  /* Reference count per process*/
    LPVOID      BasePtr;                /* Base pointer of dll load (not 0 based) */
    DWORD       DbgFlags;               /* Debug flags */
    LPDBGPARAM  ZonePtr;                /* Debug zone pointer */
    ulong       startip;                /* 0 based entrypoint */
    openexe_t   oe;                     /* Pointer to executable file handle */
    e32_lite    e32;                    /* E32 header */
    o32_lite    *o32_ptr;               /* O32 chain ptr */
    DWORD       dwNoNotify;             /* 1 bit per process, set if notifications disabled */
    WORD        wFlags;
    BYTE        bTrustLevel;
    BYTE        bPadding;
    PMODULE     pmodResource;           /* module that contains the resources */
    DWORD       rwLow;                  /* base address of RW section for ROM DLL */
    DWORD       rwHigh;                 /* high address RW section for ROM DLL */
    PGPOOL_Q    pgqueue;                /* list of the page owned by the module */
    LPVOID      pShimInfo;              /* pointer to shim information */
} Module;

typedef struct {
    HANDLE hFirstThrd;  // first thread being debugged by this thread
    HANDLE hNextThrd;   // next thread being debugged
    PCONTEXT psavedctx; // pointer to saved context, if any
    HANDLE hEvent;      // handle to wait on for debug event for this thread
    HANDLE hBlockEvent; // handle that thread is waiting on
    DEBUG_EVENT dbginfo;// debug info
    BOOL bDispatched;
} THRDDBG, *LPTHRDDBG;

/* Thread Call stack structure
 *
 *  This structure is used by the IPC mechanism to track
 * current process, access key, and return addresses for
 * IPC calls which are in progress. It is also used by
 * the exception handling code to hold critical thread
 * state while switching modes.
 */
typedef struct CALLSTACK {
    struct CALLSTACK *pcstkNext;
    RETADDR     retAddr;    /* return address */
    PPROCESS    pprcLast;   /* previous process */
    ACCESSKEY   akyLast;    /* previous access key */
    uint        extra;      /* extra CPU dependent data */
//#if defined(MIPS)
//    ulong       pPad;       /* so that excinfo fits in a callstack */
//#endif
#if defined(x86)
    ulong       ExEsp;      /* saved Esp value for exception */
    ulong       ExEbp;      /* saved Ebp   " */
    ulong       ExEbx;      /* saved Ebx   " */
    ulong       ExEsi;      /* saved Esi   " */
    ulong       ExEdi;      /* saved Edi   " */
#endif
    ulong       dwPrevSP;   /* SP of caller */
    ulong       dwPrcInfo;  /* information about the caller (mode, callback?, etc) */
} CALLSTACK;    /* CallStack */
typedef CALLSTACK *PCALLSTACK;

/* Thread data structures */

typedef struct CLEANEVENT {
    struct CLEANEVENT *ceptr;
    LPVOID base;
    DWORD size;
    DWORD op;
} CLEANEVENT, *LPCLEANEVENT;

typedef struct THREADTIME {
    struct THREADTIME *pnext;
    HANDLE hTh;
    FILETIME CreationTime;
    FILETIME ExitTime;
    FILETIME KernelTime;
    FILETIME UserTime;
} THREADTIME, *LPTHREADTIME;

typedef struct CRIT *LPCRIT;

typedef struct _CPUCONTEXT {
    ULONG Psr;
    ULONG R0;
    ULONG R1;
    ULONG R2;
    ULONG R3;
    ULONG R4;
    ULONG R5;
    ULONG R6;
    ULONG R7;
    ULONG R8;
    ULONG R9;
    ULONG R10;
    ULONG R11;
    ULONG R12;
    ULONG Sp;
    ULONG Lr;
    ULONG Pc;

    // VFP registers
    ULONG Fpscr;        // floating point status register
    ULONG FpExc;        // the exception register
    ULONG S[NUM_VFP_REGS+1];    // fstmx/fldmx requires n+1 registers
    ULONG FpExtra[NUM_EXTRA_CONTROL_REGS];
} CPUCONTEXT, *PCPUCONTEXT;

#define RUNSTATE_RUNNING 0  // must be 0
#define RUNSTATE_RUNNABLE 1
#define RUNSTATE_BLOCKED 2
#define RUNSTATE_NEEDSRUN 3 // on way to being runnable

#define WAITSTATE_SIGNALLED 0
#define WAITSTATE_PROCESSING 1
#define WAITSTATE_BLOCKED 2

#define TIMEMODE_USER 0
#define TIMEMODE_KERNEL 1

#define RUNSTATE_SHIFT       0  // 2 bits
#define DYING_SHIFT          2  // 1 bit
#define DEAD_SHIFT           3  // 1 bit
#define BURIED_SHIFT         4  // 1 bit
#define SLEEPING_SHIFT       5  // 1 bit
#define TIMEMODE_SHIFT       6  // 1 bit
#define NEEDDBG_SHIFT        7  // 1 bit
#define STACKFAULT_SHIFT     8  // 1 bit
#define DEBUGBLK_SHIFT       9  // 1 bit
#define NOPRIOCALC_SHIFT    10  // 1 bit
#define DEBUGWAIT_SHIFT     11  // 1 bit
#define USERBLOCK_SHIFT     12  // 1 bit
#ifdef DEBUG
#define DEBUG_LOOPCNT_SHIFT 13 // 1 bit - only in debug
#endif
#define NEEDSLEEP_SHIFT     14  // 1 bit
#define PROFILE_SHIFT       15  // 1 bit, must be 15!  Used by assembly code!

#define GET_BPRIO(T)        ((WORD)((T)->bBPrio))                           /* base priority */
#define GET_CPRIO(T)        ((WORD)((T)->bCPrio))                           /* current priority */
#define SET_BPRIO(T,S)      ((T)->bBPrio = (BYTE)(S))
#define SET_CPRIO(T,S)      ((T)->bCPrio = (BYTE)(S))

#define GET_TIMEMODE(T)     (((T)->wInfo >> TIMEMODE_SHIFT)&0x1)        /* What timemode are we in */
#define GET_RUNSTATE(T)     (((T)->wInfo >> RUNSTATE_SHIFT)&0x3)        /* Is thread runnable */
#define GET_BURIED(T)       (((T)->wInfo >> BURIED_SHIFT)&0x1)          /* Is thread 6 feet under */
#define GET_SLEEPING(T)     (((T)->wInfo >> SLEEPING_SHIFT)&0x1)        /* Is thread sleeping */
#define GET_DEBUGBLK(T)     (((T)->wInfo >> DEBUGBLK_SHIFT)&0x1)        /* Has DebugActive suspended thread */
#define GET_DYING(T)        (((T)->wInfo >> DYING_SHIFT)&0x1)           /* Has been set to die */
#define TEST_STACKFAULT(T)  ((T)->wInfo & (1<<STACKFAULT_SHIFT))
#define GET_DEAD(T)         (((T)->wInfo >> DEAD_SHIFT)&0x1)
#define GET_NEEDDBG(T)      (((T)->wInfo >> NEEDDBG_SHIFT)&0x1)
#define GET_PROFILE(T)      (((T)->wInfo >> PROFILE_SHIFT)&0x1)         /* montecarlo profiling */
#define GET_NOPRIOCALC(T)   (((T)->wInfo >> NOPRIOCALC_SHIFT)&0x1)
#define GET_DEBUGWAIT(T)    (((T)->wInfo >> DEBUGWAIT_SHIFT)&0x1)
#define GET_USERBLOCK(T)    (((T)->wInfo >> USERBLOCK_SHIFT)&0x1)       /* did thread voluntarily block? */
#define GET_NEEDSLEEP(T)    (((T)->wInfo >> NEEDSLEEP_SHIFT)&0x1)       /* should the thread put back to sleepq? */

#define SET_RUNSTATE(T,S)   ((T)->wInfo = (WORD)(((T)->wInfo & ~(3<<RUNSTATE_SHIFT)) | ((S)<<RUNSTATE_SHIFT)))
#define SET_BURIED(T)       ((T)->wInfo |= (1<<BURIED_SHIFT))
#define SET_SLEEPING(T)     ((T)->wInfo |= (1<<SLEEPING_SHIFT))
#define CLEAR_SLEEPING(T)   ((T)->wInfo &= ~(1<<SLEEPING_SHIFT))
#define SET_DEBUGBLK(T)     ((T)->wInfo |= (1<<DEBUGBLK_SHIFT))
#define CLEAR_DEBUGBLK(T)   ((T)->wInfo &= ~(1<<DEBUGBLK_SHIFT))
#define SET_DYING(T)        ((T)->wInfo |= (1<<DYING_SHIFT))
#define SET_STACKFAULT(T)   ((T)->wInfo |= (1<<STACKFAULT_SHIFT))
#define CLEAR_STACKFAULT(T) ((T)->wInfo &= ~(1<<STACKFAULT_SHIFT))
#define SET_DEAD(T)         ((T)->wInfo |= (1<<DEAD_SHIFT))
#define SET_TIMEUSER(T)     ((T)->wInfo &= ~(1<<TIMEMODE_SHIFT))
#define SET_TIMEKERN(T)     ((T)->wInfo |= (1<<TIMEMODE_SHIFT))
#define SET_NEEDDBG(T)      ((T)->wInfo |= (1<<NEEDDBG_SHIFT))
#define CLEAR_NEEDDBG(T)    ((T)->wInfo &= ~(1<<NEEDDBG_SHIFT))
#define SET_PROFILE(T)      ((T)->wInfo |= (1<<PROFILE_SHIFT))
#define CLEAR_PROFILE(T)    ((T)->wInfo &= ~(1<<PROFILE_SHIFT))
#define SET_NOPRIOCALC(T)   ((T)->wInfo |= (1<<NOPRIOCALC_SHIFT))
#define CLEAR_NOPRIOCALC(T) ((T)->wInfo &= ~(1<<NOPRIOCALC_SHIFT))
#define SET_DEBUGWAIT(T)    ((T)->wInfo |= (1<<DEBUGWAIT_SHIFT))
#define CLEAR_DEBUGWAIT(T)  ((T)->wInfo &= ~(1<<DEBUGWAIT_SHIFT))
#define SET_USERBLOCK(T)    ((T)->wInfo |= (1<<USERBLOCK_SHIFT))
#define CLEAR_USERBLOCK(T)  ((T)->wInfo &= ~(1<<USERBLOCK_SHIFT))
#define SET_NEEDSLEEP(T)    ((T)->wInfo |= (1<<NEEDSLEEP_SHIFT))
#define CLEAR_NEEDSLEEP(T)  ((T)->wInfo &= ~(1<<NEEDSLEEP_SHIFT))

struct Thread {
    WORD        wInfo;      /* 00: various info about thread, see above */
    BYTE        bSuspendCnt;/* 02: thread suspend count */
    BYTE        bWaitState; /* 03: state of waiting loop */
    LPPROXY     pProxList;  /* 04: list of proxies to threads blocked on this thread */
    PTHREAD     pNextInProc;/* 08: next thread in this process */
    PPROCESS    pProc;      /* 0C: pointer to current process */
    PPROCESS    pOwnerProc; /* 10: pointer to owner process */
    ACCESSKEY   aky;        /* 14: keys used by thread to access memory & handles */
    PCALLSTACK  pcstkTop;   /* 18: current api call info */
    DWORD       dwOrigBase; /* 1C: Original stack base */
    DWORD       dwOrigStkSize;  /* 20: Size of the original thread stack */
    LPDWORD     tlsPtr;     /* 24: tls pointer */
    DWORD       dwWakeupTime; /* 28: sleep count, also pending sleepcnt on waitmult */
    LPDWORD     tlsSecure;      /* 2c: TLS for secure stack */
    LPDWORD     tlsNonSecure;   /* 30: TLS for non-secure stack */
    LPPROXY     lpProxy;    /* 34: first proxy this thread is blocked on */
    DWORD       dwLastError;/* 38: last error */
    HANDLE      hTh;        /* 3C: Handle to this thread, needed by NextThread */
    BYTE        bBPrio;     /* 40: base priority */
    BYTE        bCPrio;     /* 41: curr priority */
    WORD        wCount;     /* 42: nonce for blocking lists */
    PTHREAD     pPrevInProc;/* 44: previous thread in this process */
    LPTHRDDBG   pThrdDbg;   /* 48: pointer to thread debug structure, if any */
    LPBYTE      pSwapStack; /* 4c */
    FILETIME    ftCreate;   /* 50: time thread is created */
    CLEANEVENT *lpce;       /* 58: cleanevent for unqueueing blocking lists */
    DWORD       dwStartAddr; /* 5c: thread PC at creation, used to get thread name */
    CPUCONTEXT  ctx;        /* 60: thread's cpu context information */
    PTHREAD     pNextSleepRun; /* ??: next sleeping thread, if sleeping, else next on runq if runnable */
    PTHREAD     pPrevSleepRun; /* ??: back pointer if sleeping or runnable */
    PTHREAD     pUpRun;     /* ??: up run pointer (circulaar) */
    PTHREAD     pDownRun;   /* ??: down run pointer (circular) */
    PTHREAD     pUpSleep;   /* ??: up sleep pointer (null terminated) */
    PTHREAD     pDownSleep; /* ??: down sleep pointer (null terminated) */
    LPCRIT      pOwnedList; /* ??: list of crits and mutexes for priority inversion */
    LPCRIT      pOwnedHash[PRIORITY_LEVELS_HASHSIZE];
    DWORD       dwQuantum;  /* ??: thread quantum */
    DWORD       dwQuantLeft;/* ??: quantum left */
    LPPROXY     lpCritProxy;/* ??: proxy from last critical section block, in case stolen back */
    LPPROXY     lpPendProxy;/* ??: pending proxies for queueing */
    DWORD       dwPendReturn;/* ??: return value from pended wait */
    DWORD       dwPendTime; /* ??: timeout value of wait operation */
    PTHREAD     pCrabPth;
    WORD        wCrabCount;
    WORD        wCrabDir;
    DWORD       dwPendWakeup;/* ??: pending timeout */
    WORD        wCount2;    /* ??: nonce for SleepList */
    BYTE        bPendSusp;  /* ??: pending suspend count */
    BYTE        bDbgCnt;    /* ??: recurse level in debug message */
    HANDLE      hLastCrit;  /* ??: Last crit taken, cleared by nextthread */
    //DWORD     dwCrabTime;
    CALLSTACK   IntrStk;
    DWORD       dwKernTime; /* ??: elapsed kernel time */
    DWORD       dwUserTime; /* ??: elapsed user time */
    HANDLE      hTok;       /* ??: thread token */
};  /* Thread */

#define THREAD_CONTEXT_OFFSET   0x60

#define HANDLE_ADDRESS_MASK 0x1ffffffc

//---------------------------------------------------------------------------
// getProcess -
//   Retrieves the pointer to the process information
//===========================================================================
inline PPROCESS getProcess(HANDLE hProc)
{
	HDATA *hd = (HDATA*)(0x80000000 | ((DWORD)hProc & HANDLE_ADDRESS_MASK));
	return (PPROCESS)hd->pvObj;
};

//---------------------------------------------------------------------------
// getThread -
//   Retrieves the pointer to the thread information
//===========================================================================
inline PTHREAD getThread(HANDLE hThread)
{
	HDATA *hd = (HDATA*)(0x80000000 | ((DWORD)hThread & HANDLE_ADDRESS_MASK));
	return (PTHREAD)hd->pvObj;
};

//---------------------------------------------------------------------------
// GetModuleBaseAddress -
//    Return module base address by its HMODULE
//===========================================================================
inline DWORD GetModuleBaseAddress(HMODULE hMod)
{
	if((DWORD)hMod==GetCurrentProcessId())	// под CE hMod ЕХЕ-файла соответствует hProcess
	{
		return (DWORD)getProcess((HANDLE)hMod)->BasePtr;
	} else
	{
		return (DWORD)((LPMODULE)hMod)->BasePtr;
	}
};


#endif
