#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

/* Linker magic so we can be both a shared library and an executable. */
const char service_interp[] __attribute__((section(".interp"))) = "/lib64/ld-linux-x86-64.so.2";

void
callback (void)
{
        fprintf (stderr, "Welcome back, world.\n");
}

int
main (int argc, char **argv)
{
        void    *plugin;
        void    (*func) (void);

        plugin = dlopen ("./dyn-plugin.so", RTLD_NOW | RTLD_GLOBAL);
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

        exit (EXIT_SUCCESS);
}
