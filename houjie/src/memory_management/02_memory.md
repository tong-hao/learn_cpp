
## c++ memory primitives
1) c语言
malloc() free() 不可重载
```
void* p1 = malloc(512); // 512bytes
free(p1);
```

2）c++表达式
new, delete 不可重载
```
complex<int> *c = new complex<int>();
delete c;
```

3）c++函数
::operator new()
::operator delete()
可以重载

```
void* p3 = ::operator new(512); 
::operator delete(p3);
```

4）c++标准库
allocator<T>::allocate()
allocator<T>::deallocate()
可以自己设计
```
#ifdef __GNUC__
// non-static
void* p4 = allocator<int>().allocate(7); // 7 ints
allocator<int>().deallocate(p4, 512);
#endif
```


