//
//  KindKit2
//

import Foundation

public protocol IString {
    
    var encoding: String.Encoding { get }
    var capacity: UInt { get }
    var length: UInt { get }
    var count: UInt { get }
    var isEmpty: Bool { get }
    var startIndex: UInt { get }
    var endIndex: UInt { get }
    var range: String.Range { get }
    
    func `is`< Equal : IUnsafeString >(equal: Equal) -> Bool
    func `is`< Prefix : IUnsafeString >(prefix: Prefix) -> Bool
    func `is`< Suffix : IUnsafeString >(suffix: Suffix) -> Bool
    func find< First : IUnsafeString >(first: First, in range: String.Range) -> String.Range
    func find< Last : IUnsafeString >(last: Last, in range: String.Range) -> String.Range
    
}

public extension IString {
    
    @inlinable
    func find< First : IUnsafeString >(first: First) -> String.Range {
        return self.find(first: first, in: self.range)
    }
    
    @inlinable
    func find< Last : IUnsafeString >(last: Last) -> String.Range {
        return self.find(last: last, in: self.range)
    }
    
}

public protocol IMutableString : IString {
    
    func clear()

    @discardableResult
    func fit() -> Bool
    
    @discardableResult
    func insert< Insert : IUnsafeString >(_ string: Insert, at index: UInt) -> Bool
    
    @discardableResult
    func prepend< Insert : IUnsafeString >(_ string: Insert) -> Bool
    
    @discardableResult
    func append< Insert : IUnsafeString >(_ string: Insert) -> Bool
    
    @discardableResult
    func remove(in range: String.Range) -> UInt
    
    @discardableResult
    func remove< Search : IUnsafeString >(first: Search, in range: String.Range) -> UInt
    
    @discardableResult
    func remove< Last : IUnsafeString >(last: Last, in range: String.Range) -> UInt
    
    @discardableResult
    func remove< All : IUnsafeString >(all: All, in range: String.Range) -> UInt
    
    @discardableResult
    func replace< To : IUnsafeString >(range: String.Range, to: To) -> Bool
    
    @discardableResult
    func replace< First : IUnsafeString, To : IUnsafeString >(first: First, to: To, in range: String.Range) -> Bool
    
    @discardableResult
    func replace< Last : IUnsafeString, To : IUnsafeString >(last: Last, to: To, in range: String.Range) -> Bool
    
    @discardableResult
    func replace< All : IUnsafeString, To : IUnsafeString >(all: All, to: To, in range: String.Range) -> UInt
    
}

public extension IMutableString {

    @inlinable
    @discardableResult
    func remove< Search : IUnsafeString >(first: Search) -> UInt {
        return self.remove(first: first, in: self.range)
    }
    
    @inlinable
    @discardableResult
    func remove< Search : IUnsafeString >(last: Search) -> UInt {
        return self.remove(last: last, in: self.range)
    }
    
    @inlinable
    @discardableResult
    func remove< All : IUnsafeString >(all: All) -> UInt {
        return self.remove(all: all, in: self.range)
    }
    
    @inlinable
    @discardableResult
    func replace< First : IUnsafeString, To : IUnsafeString >(first: First, to: To) -> Bool {
        return self.replace(first: first, to: to, in: self.range)
    }
    
    @inlinable
    @discardableResult
    func replace< Last : IUnsafeString, To : IUnsafeString >(last: Last, to: To) -> Bool {
        return self.replace(last: last, to: to, in: self.range)
    }
    
    @inlinable
    @discardableResult
    func replace< All : IUnsafeString, To : IUnsafeString >(all: All, to: To) -> UInt {
        return self.replace(all: all, to: to, in: self.range)
    }

}
