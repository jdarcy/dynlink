extern void good_callback (void);
extern void bad_callback (void);

__attribute__((visibility("default")))
void
gauche (void)
{
        /* This works. */
        good_callback ();

#if 0
        /* This doesn't work because good_callback is not exported. */
        bad_callback ();
#endif
}
