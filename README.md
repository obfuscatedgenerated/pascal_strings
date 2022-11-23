# Pascal Strings
> Demonstration of Pascal strings in C.

## What are Pascal strings?

Pascal strings are a method of storing string data by prepending the length of the string at the start, rather than appending a null byte. This has some key advantages, such as optimisation (think iteration) and string handling safety (e.g. missing null byte), as well as preventing the need to pass the string length or predict it using strlen when using certain functions.

They were first implemented in the UCSD implementation of the Pascal programming language, hence the name.

## Examples of use cases

They can be found in a variety of programs, but the most famously known implementation is in Microsoft Excel (accurate as of [2010](https://stackoverflow.com/questions/492384/how-to-find-the-size-of-an-array-from-a-pointer-pointing-to-the-first-element-a#comment3358256_492428)).
