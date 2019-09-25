//
//  BRBase.h
//  BRCore
//
//  Created by Michael Carrara on 7/1/19.
//  Copyright © 2019 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#ifndef BRBase_h
#define BRBase_h

#ifdef __cplusplus
extern "C" {
#endif

#define OwnershipGiven
#define OwnershipKept

// Address: "Value Store in `var` is never read"
#ifdef __clang_analyzer__
#  define ANALYZER_IGNORE_UNREAD_VARIABLE(var)     ((void) var)
#else
#  define ANALYZER_IGNORE_UNREAD_VARIABLE(var)
#endif

#ifdef __cplusplus
}
#endif

#endif /* BRBase_h */
