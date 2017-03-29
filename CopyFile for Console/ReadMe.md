CopyFile
-----------

* console base의 파일을 copy 하는 프로그램 입니다.
* 일반적인 copy 프로그램과는 달리, **대상 경로에 파일이 있어야 덮어 씁니다.**
* 원본경로에는 파일이 있지만, 대상경로에 파일이 없으면 파일을 copy 하지 않습니다.
* 사용 방법은 아래와 같습니다.

```
Used>
> cpfiles [option]

[option]
        -c : config file
        -l : log file
        -s : source parent directory
        -d : destination parent directory

ex> cpfiles.exe -c list.cfg -l secure.log -s c:\secure_bin -d d:\secure_package\binary
```
