# Pascal Strings
> Demonstration of Pascal strings in C.

## What are Pascal strings?

Pascal strings are a method of storing string data by prepending the length of the string at the start, rather than appending a null byte. This has some key advantages, such as optimisation *(think iteration)* and string handling safety *(e.g. missing null byte)*, as well as preventing the need to pass the string length or predict it using `strlen` when using certain functions.

They were first implemented in the UCSD implementation of the *Pascal* programming language, hence the name.

## Examples of use cases

They can be found in a variety of programs, but the most famously known implementation is in *Microsoft Excel* (accurate as of [2010](https://stackoverflow.com/questions/492384/how-to-find-the-size-of-an-array-from-a-pointer-pointing-to-the-first-element-a#comment3358256_492428)).

## One big drawback

As a single unsigned integer takes up 1 byte, the size is limited to 255 characters.

# Super Strings

This is a method that I made up (although I'm sure it's been done before) that I dub "super strings". It's a method of storing strings in a similar way to Pascal strings, but rather than storing a single value that is the exact value of the length, we use 2 bytes. The first one is multiplied by the maximum unsigned char value (255) and added to the second one. This allows for a maximum length of 65,280 characters.

Initially, the format was that the first byte indicated the number of bytes that followed to be added to each other, but I realised that repeating 255 over and over is not efficient. The new method is more efficient, but it means incompatibility with systems that don't use the same maximum unsigned char value when sent over the network. However, this is not a problem for local use and I have never seen a system that uses a different maximum unsigned char value (not counting when unicode/wchar is expressly opted into).
