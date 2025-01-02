### Getting IPv6 in C ###

This is one of way of getting IPv6 in C, and it also only works for linux
environment, since the retrieval of IPv6 in this approach came from specific
file in linux.

/proc/net/if_inet6

It contains the IPv6 including interface name, etc.

```c
FILE* file = fopen("/proc/net/if_inet6", "r");
```
This process of getting the IPv6 able to happen by reading the file contents.

```c
char buf[128];
```

Initialized a variable with a size of 128 bytes of char.

There are two ways that can be used to read a line in file. The first option
function is the get() function but the contrains is it will read the entire
line and since the IPv6 and the interface name typically at the beginning of
the contents reading the entire line is not efficient. Thereby the second
option is perfect for this instance, which is the fgets() function.

while(fgets(buf, sizeof(buf), file)) {}

With the help of while loop it will consistently read line by line.
The first parameter will be the container of read contents.
The second is to help the fgets to determine when it should stop reading.
And the last is the actual binary or buffer since fopen probably used buffer
for transfering it in i/o.

```c
char raw_ipv6[31], devname[20];
sscanf(buf, "%32s %*02x %*02x %*02x %*02x %19s", raw_ipv6, devname);
```

The sscanf will help to find the IPv6 and interface name by specifying the
format needed for searching.
The first parameter is the line read by fgets().
Second parameter is the string format needs for searching.
The third and fourth parameters are only depends on the second parameter
which is the string format, so they are the containers or placeholder for
searched contents.

```c
strcmp(devname, iface)
```

strcmp to compare the interface found in the file from the interface specified
by the user.

If all of these process succeeded user would able to get the IPv6 but in a raw
format of hexadecimal(128 bits), 128 bits since it contains 32 character and
char is actually identical on integer of 4 bytes.

  - 32 bytes is 128bits

In order to make it in a format of IPv6 standard notation, where every 4
hexadecimal is separated by colons.

```c
void formatIPv6(const char* raw, char* formatted) {
    // Add colons every 4 characters
    for(int i = 0, j = 0; i < 32; i++) {
        formatted[j++] = raw[i];
        if((i+1)%4 == 0 && i != 31) {
            formatted[j++] = ':';
        }
    }
    formatted[39] = '\0'; // Null-terminate the string
}
```

The formatIPv6 function will handle that. Additionally if you're wondering
why some of IPv6 only has 6 segments of hexadecimal is it because, casually
they omit each segments with series of zeros and it cout be easily identified
by if it has double colons after the first segment. And that first four
hexadecimal also indicates a link-local IPv6 address. In this instance I don't
want to dive in further in IPv6 since it may be another long rabbit hole.
