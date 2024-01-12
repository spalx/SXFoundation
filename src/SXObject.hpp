/**
 * @file SXObject.hpp
 * @brief Declaration of the SXObject class.
 *
 * @copyright (c) 2024 Artavazd Barseghyan
 * @details This software is released under the MIT License.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SXObject_hpp
#define SXObject_hpp

#include "SXCommon.hpp"

namespace spalx {

/**
 * @class SXObject
 * @brief Base class from which all other classes are derived.
 */
class SXObject
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes the object with reference count set to 1.
     */
    SXObject();
    
    /**
     * @brief Destructor.
     * @details Declared as virtual, so when we delete an instance of a derived class through a pointer to SXObject the destructor of the derived class gets called.
     */
    virtual ~SXObject();
    
    /**
     * @brief Decrease reference count by 1.
     * @details If reference count reached 0, the object is deleted.
     */
    void release();
    
    /**
     * @brief Increase reference count by 1.
     */
    void retain();
    
    /**
     * @brief Mark object as autorelease.
     * @details Objects marked as autorelease are added to the current autorelease pool. When the autorelease pool gets drained, they are released.
     * @return The object itself.
     */
    SXObject* autorelease();
    
    /**
     * @brief Get current reference count.
     * @return The reference count.
     */
    unsigned int retainCount() const;
    
    /**
     * @brief Compare with other object (mainly in a deep manner).
     * @return Whether both objects are equal.
     */
    virtual bool isEqual(const SXObject* pObject) const;
    
    /**
     * @brief Perform a deep copy of the object.
     * @details When arrays, dictionaries or sets are copied, this method is called on each child element. So in order to make any derived class from SXObject clonable, this method must be properly implemented.
     * @return The new copied object.
     */
    virtual SXObject* copy() const;
    
protected:
    unsigned int m_referenceCount{1}; /**< Reference count. */
};

} // namespace spalx

#endif // SXObject_hpp
