// foo.h
#ifdef __cplusplus
extern "C" {
#endif
  typedef void* Foo;
  Foo FooInit(void);
  void FooFree(Foo);
  void FooBar(Foo);
#ifdef __cplusplus
}
#endif
