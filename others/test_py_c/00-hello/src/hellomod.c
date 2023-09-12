#include <Python.h>

#define UNUSED(x) (void)(x)

static PyObject *helloc(PyObject *self, PyObject *args)
{
    UNUSED(self);

    const char *name;
    if (!PyArg_ParseTuple(args, "s", &name))
        return NULL;

    printf("Hello %s\n", name);
    Py_RETURN_NONE;
}

static PyMethodDef helloc_methods[] = {
    {"helloc", (PyCFunction)helloc, METH_VARARGS, "says hello to somebody (in C)"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef hellolib_struct = {
    PyModuleDef_HEAD_INIT,
    "hellolib",
    "hellolib module has some dumb things",
    -1,
    helloc_methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC PyInit_hellolib(void)
{
    return PyModule_Create(&hellolib_struct);
}
