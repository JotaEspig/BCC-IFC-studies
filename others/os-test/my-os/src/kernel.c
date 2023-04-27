extern void main()
{
    char *screen_ptr = (char *)0xb8000;
    char msg[] = "Hello World!";
    for (int i = 0; i < sizeof(msg) / sizeof(char); i++)
    {
        *screen_ptr = msg[i];
        screen_ptr += 2;
    }
    return;
}
