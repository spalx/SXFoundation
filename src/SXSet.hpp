/**
 * @file SXSet.hpp
 * @brief Declaration of the SXSet class.
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

#ifndef SXSet_hpp
#define SXSet_hpp

#include "SXObject.hpp"
#include <unordered_set>

namespace spalx {

typedef std::unordered_set<SXObject*>::iterator SXSetIterator;
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Type definition for an iterator over an unordered_set with SXObject* values.

/**
 * @class SXSet
 * @brief Unordered collection of distinct objects.
 */
class SXSet : public SXObject
{
public:
    /**
     * @brief Default constructor.
     * @details Initializes the unordered set.
     */
    SXSet();
    
    /**
     * @brief Destructor.
     * @details Before set deletion, removes all objects from the set so their reference count gets decreased by 1.
     */
    ~SXSet();
    
    /**
     * @brief Create a new set.
     * @return The new set object. nullptr if initialization fails.
     */
    static SXSet* create();
    
    /**
     * @brief Get the number of elements in the set.
     * @return The number of elements.
     */
    unsigned int count() const;
    
    /**
     * @brief Add the object to the set, if it is not already a member.
     */
    void addObject(SXObject* pObject);
    
    /**
     * @brief Check whether the set has a specific object.
     * @param pObject The object to find.
     * @return Whether object exists in the set.
     */
    bool containsObject(SXObject* pObject) const;
    
    /**
     * @brief Remove object from the set.
     * @details The reference count of the object is decreased by 1.
     * @param pObject The object to remove.
     */
    void removeObject(SXObject* pObject);
    
    /**
     * @brief Remove all objects from the set.
     * @details The reference count of each object is decreased by 1.
     */
    void removeAllObjects();

    /**
     * @brief Get the first element of the set.
     * @return An iterator over the first element of the unordered_set.
     */
    SXSetIterator begin() const;
    
    /**
     * @brief Get the last element of the set.
     * @return An iterator over the last element of the unordered_set. If iterator reaches here, means that there are no more objects in the set.
     */
    SXSetIterator end() const;
    
    /**
     * @brief Get one of the objects in the set.
     * @return The object.
     */
    SXObject* anyObject() const;
    
    /**
     * @brief Perform a deep copy of the set.
     * @details Create a new set by copying (copy() is called) each element inside the set.
     * @return The new copied set.
     */
    virtual SXObject* copy() const override;
    
private:
    std::unordered_set<SXObject*>* m_pSet; /**< Set container of all objects. */
};

} // namespace spalx

#endif // SXSet_hpp
