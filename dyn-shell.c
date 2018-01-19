#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

/* Linker magic so we can be both a shared library and an executable. */
const char service_interp[] __attribute__((section(".interp"))) = "/lib64/ld-linux-x86-64.so.2";

__attribute__((visibility("default")))
void
good_callback (void)
{
        printf ("Welcome back, world.\n");
}

void
bad_callback (void)
{
        printf ("What am I doing here?\n");
}

int
main (int argc, char **argv)
{
        void    *plugin;
        void    (*func) (void);

        plugin = dlopen ("./dyn-plugin.so", RTLD_NOW | RTLD_LOCAL);
        if (!plugin) {
                fprintf (stderr, "load failed (%s)\n", dlerror());
                return EXIT_FAILURE;
        }

        /* "Main gauche" is a French name for a parrying dagger. */
        func = dlsym (plugin, "gauche");
        if (!func) {
                fprintf (stderr, "lookup failed (%s)\n", dlerror());
                return EXIT_FAILURE;
        }

        func ();

        return EXIT_SUCCESS;
}

int
entry (int argc, char **argv)
{
        exit (main (argc, argv));
}
