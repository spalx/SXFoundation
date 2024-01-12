/**
 * @file SXPoolManager.hpp
 * @brief Declaration of the SXPoolManager class.
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

#ifndef SXPoolManager_hpp
#define SXPoolManager_hpp

#include "SXObject.hpp"
#include "SXArray.hpp"
#include "SXAutoreleasePool.hpp"
#include <mutex>

namespace spalx {

/**
 * @class SXPoolManager
 * @brief Container class for all autorelease pool objects.
 * @details Works with the LIFO principle, the last pool pushed is always the current pool and it's the pool that gets popped first.
 * @note This class is intended for use in a multithreaded environment. Ensure proper synchronization when accessing shared instances.
 */
class SXPoolManager
{
public:
    /**
     * @brief Deleted copy constructor to enforce the singleton pattern.
     */
    SXPoolManager(const SXPoolManager&) = delete;
    
    /**
     * @brief Deleted copy assignment operator to enforce the singleton pattern.
     */
    SXPoolManager& operator=(const SXPoolManager&) = delete;
    
    /**
     * @brief Get the singleton instance of this class.
     * @details When called for the first time, it creates and pushes an empty autorelease pool.
     * @return The unique instance of the pool manager.
     */
    static SXPoolManager* sharedPoolManager();
    
    /**
     * @brief Purge the pool manager.
     * @details It completely deletes the pool manager, therefore forcing all pools to be deleted and consequently releasing all objects from memory. Calling this method is a must and it should be done only at the end of the program.
     */
    static void purgePoolManager();
    
    /**
     * @brief Create and push a new autorelease pool.
     */
    void push();
    
    /**
     * @brief Pop the last/current autorelease pool.
     */
    void pop();
    
    /**
     * @brief Add an object to the current pool.
     * @param pObject The object to add to the pool.
     */
    void addObject(SXObject* pObject);
    
    /**
     * @brief Remove an object from the current pool.
     * @param pObject The object to remove from the pool.
     */
    void removeObject(SXObject* pObject);

private:
    static SXPoolManager* pInstance; /**< The singleton instance of the pool manager. */
    static std::mutex mutex; /**< Mutex for thread-safe operations on the singleton instance. */
    
    SXArray* m_pPools{nullptr}; /**< The array of autorelease pools. */
    SXAutoreleasePool* m_pCurrentPool{nullptr}; /**< The current autorelease pool. */
    
    /**
     * @brief Private constructor to prevent external instantiation.
     * @details The constructor is private to ensure that the class is only instantiated through the sharedPoolManager() method.
     */
    SXPoolManager();
    
    /**
     * @brief Destructor.
     */
    ~SXPoolManager();
};

} // namespace spalx

#endif // SXPoolManager_hpp
