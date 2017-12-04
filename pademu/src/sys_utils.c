//sio2man hook code taken from opl mcemu:
/*
  Copyright 2006-2008, Romz
  Copyright 2010, Polo
  Licenced under Academic Free License version 3.0
  Review OpenUsbLd README & LICENSE files for further details.
*/

#include "pademu.h"
#include "loadcore.h"


//---------------------------------------------------------------------------
/* Returns a pointer to a library entry table */
void *GetExportTable(char *libname, int version)
{
    iop_library_table_t *plt;
    struct _iop_library * plib;
    int i = 0;

    printf("\nstart library entry table\n\n");
    plt = GetLibraryEntryTable();
    for (plib = plt->tail; plib != plt->head && plib != NULL; plib = plib->prev) {
        i++;
        printf("%i: ", i);
        printf("%c%c%c%c%c%c%c%c", plib->name[0], plib->name[1], plib->name[2], plib->name[3], plib->name[4], plib->name[5], plib->name[6], plib->name[7]);
        printf(" - 0x%x \n", plib->version);
    }
    printf("\nend library entry table\n\n");

    if (libname != NULL) {
        iop_library_t lib;
        register int i;
        register char *psrc;

        mips_memset(&lib, 0, sizeof(iop_library_t));
        lib.version = version;

        for (i = 0, psrc = libname; (i < 8) && (*psrc); i++, psrc++)
            lib.name[i] = *psrc;

        return QueryLibraryEntryTable(&lib);
    }

    return NULL;
}
//------------------------------
//endfunc
//---------------------------------------------------------------------------
/* Returns number of entries in the export table */
u32 GetExportTableSize(void *table)
{
    register void **exp;
    register u32 size;

    exp = (void **)table;
    size = 0;

    if (exp != NULL)
        while (*exp++ != NULL)
            size++;

    return size;
}
//------------------------------
//endfunc
//---------------------------------------------------------------------------
/* Returns an entry from the export table */
void *GetExportEntry(void *table, u32 entry)
{
    if (entry < GetExportTableSize(table)) {
        register void **exp;

        exp = (void **)table;

        return exp[entry];
    }

    return NULL;
}
//------------------------------
//endfunc
//---------------------------------------------------------------------------
/* Replaces an entry in the export table */
void *HookExportEntry(void *table, u32 entry, void *func)
{
    if (entry < GetExportTableSize(table)) {
        int oldstate;
        register void **exp, *temp;

        exp = (void **)table;
        exp = &exp[entry];

        CpuSuspendIntr(&oldstate);
        temp = *exp;
        *exp = func;
        func = temp;
        CpuResumeIntr(oldstate);

        return func;
    }

    return NULL;
}
//------------------------------
//endfunc
//---------------------------------------------------------------------------
