/**
 * @file SXSelector.hpp
 * @brief Declaration and implementation of the SXSelector class.
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

#ifndef SXSelector_hpp
#define SXSelector_hpp

#include "SXObject.hpp"
#include <memory>
#include <utility>

namespace spalx {

/**
 * @brief Simple polymorphic function wrapper.
 * @details It can store, copy, and invoke any Callable target with a specific signature.
 */
template <typename Signature>
class SXSelector;

/**
 * @brief The SXSelector class specialization for a specific signature.
 */
template <typename ReturnType, typename... Args>
class SXSelector<ReturnType(Args...)> : public SXObject
{
public:
    /**
     * @brief Constructor that takes a function pointer and stores it in the selector wrapper.
     * @param pFunction The function pointer to be stored.
     */
    SXSelector(ReturnType (*pFunction)(Args...))
            : m_callable(std::make_unique<SXFunctionPointerWrapper>(pFunction)) {}
    
    /**
     * @brief Constructor that takes a callable target and stores it in the selector wrapper.
     * @tparam Callable The type of the callable target.
     * @param rCallable The callable target to be stored.
     */
    template <typename Callable>
    SXSelector(Callable&& rCallable) : m_callable(std::make_unique<SXCallableWrapper<Callable>>(std::forward<Callable>(rCallable))) {}
    
    /**
     * @brief Function call operator that invokes the stored callable with the given arguments.
     * @param args The arguments to be passed to the stored callable.
     * @return The result of the callable invocation.
     */
    ReturnType operator()(Args... args) const {
        return m_callable->operator()(std::forward<Args>(args)...);
    }
    
private:
    /**
     * @brief The SXCallableBase struct represents the type-erased callable storage.
     */
    struct SXCallableBase {
        /**
         * @brief Virtual function for invoking the stored callable with the given arguments.
         * @return The result of the callable invocation.
         */
        virtual ReturnType operator()(Args...) const = 0;
        
        /**
         * @brief Virtual destructor for proper cleanup.
         */
        virtual ~SXCallableBase() = default;
    };
    
    /**
     * @brief The SXCallableWrapper struct represents a concrete callable wrapper with a specific type.
     */
    template <typename Callable>
    struct SXCallableWrapper : SXCallableBase {
        /**
         * @brief Constructor that takes a callable target and stores it in the wrapper.
         * @param rCallable The callable target to be stored.
         */
        SXCallableWrapper(Callable&& rCallable) : m_callable(std::forward<Callable>(rCallable)) {}

        /**
         * @brief Function call operator that invokes the stored callable with the given arguments.
         * @param args The arguments to be passed to the stored callable.
         * @return The result of the callable invocation.
         */
        ReturnType operator()(Args... args) const {
            return m_callable(std::forward<Args>(args)...);
        }

        Callable m_callable; /**< The stored callable target of a specific type. */
    };
    
    /**
     * @brief The SXFunctionPointerWrapper struct represents a concrete wrapper for function pointers.
     */
    struct SXFunctionPointerWrapper : SXCallableBase {
        ReturnType (*m_pFunction)(Args...); /**< Function pointer to be stored. */

        /**
         * @brief Explicit constructor that takes a function pointer and initializes the wrapper.
         * @param pFunction The function pointer to be stored.
         */
        explicit SXFunctionPointerWrapper(ReturnType (*pFunction)(Args...))
            : m_pFunction(pFunction) {}

        /**
         * @brief Function call operator that invokes the stored function pointer with the given arguments.
         * @param args The arguments to be passed to the stored function pointer.
         * @return The result of the function pointer invocation.
         */
        ReturnType operator()(Args... args) const override {
            return m_pFunction(std::forward<Args>(args)...);
        }
    };
    
    std::unique_ptr<SXCallableBase> m_callable; /**< The type-erased callable storage. */
};

} // namespace spalx

#endif // SXSelector_hpp
