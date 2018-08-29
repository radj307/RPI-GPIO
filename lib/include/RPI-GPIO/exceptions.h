/*

MIT License

Copyright (c) 2018 Guillaume Bauer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <string>

#pragma once


/**
 * Exception base class
 * Represents a generic exception
 * Has only basic functionnalities (exception message)
 * The exception message is fetched from the standard error code
 */
class Exception {
    private:
        const std::string message;  // Exception message
        const int err;            // Error number

    public:
        /**
         * Constructor
         * @param error error code
         */
        explicit Exception(const int error);

        /**
         * Getter for the exception message
         * @return the exception message
         */
        const std::string& what(void) const;

        /**
         * Getter for the error number
         * @return the error number
         */
        int error(void) const;
};



/**
 * Every exception is just a type specification from the base Exception class
 */
class IOException : public Exception {
    public:
        IOException(const int error) : Exception{error} {}
};

class MemoryException : public Exception {
    public:
        MemoryException(const int error) : Exception{error} {}
};