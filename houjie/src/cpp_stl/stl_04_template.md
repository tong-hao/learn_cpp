
# 模版分类
## 1.函数模板
```
template <T>
T& min(const T& a, const T& b){
    return a > b ? b : a;
}

min<double>(1.1, 1.2);

```

## 2.类模板
```
template<typename T>
class Test{
    public:
        T getObj(){return obj;}

    private:
        T obj;
}

```

## 3.特化
### 3.1特化/全特化
```
// 泛化
template <typename T>
void call(T t){}

// 特化
template <typename bool>
void call<bool>(bool t){}

```

### 3.2偏特化-情况1：局部
```
// 泛化
template <typename T1, typename T2>
void call(T1 t1, T2 t2){}

// 偏特化
template <typename T2>
void call<bool, T2>(bool t1, T2 t2){}

// 偏特化
template <>
void call<bool, int>(bool t1, int t2){}

```

### 3.3偏特化-情况2:范围
```
template <typename T>
void call(T t){}


template <T>
void call<T1*>(T1 t1){}

```
