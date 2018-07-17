my_str = "interface=com.alibaba.dubbo.performance.demo.provider.IHelloService&method=hash&parameterTypesString=" \
         "Ljava%2Flang%2FString%3B&parameter=Tbk4ZGqnHQNRM8Wqr65Sxz8K2wnWHhvcaNuAnTn64geI6AnEHB8cCtEg154"

print my_str
print ''.join(reversed([ch for ch in my_str[0:16]]))