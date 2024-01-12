/**
 * @file SXAutoreleasePool.hpp
 * @brief Declaration of the SXAutoreleasePool class.
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

#ifndef SXAutoreleasePool_hpp
#define SXAutoreleasePool_hpp

#include "SXObject.hpp"
#include "SXArray.hpp"

namespace spalx {

/**
 * @class SXAutoreleasePool
 * @brief Container class for all autorelease objects.
 * @details The autorelease pool stores objects marked as autorelease. These objects are sent a release message when the pool itself is drained.
 */
class SXAutoreleasePool : public SXObject
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes the array of objects.
     */
    SXAutoreleasePool();
    
    /**
     * @brief Destructor.
     * @details Deletes the array of objects.
     */
    ~SXAutoreleasePool();
    
    /**
     * @brief Add object to the pool.
     * @param pObject The object to add to the pool.
     */
    void addObject(SXObject* pObject);
    
    /**
     * @brief Remove object from the pool.
     * @param pObject The object to remove from the pool.
     */
    void removeObject(SXObject* pObject);

    /**
     * @brief Remove all objects in the pool.
     */
    void clear();

private:
    SXArray* m_pObjects{nullptr}; /**< Array of objects. */
};

} // namespace spalx

#endif // SXAutoreleasePool_hpp
