# Для компиляции и прошивки

```bash
$ make all
```

```bash
$ sudo openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c \
"init; reset halt; flash write_image erase main.hex; "\  
"reset; exit"
```

## Если надо выключить процесс openBCD

```bash
sudo lsof -i -P | grep LISTEN | grep :6666
sudo kill -9 25580
```
