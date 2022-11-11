//
//  KindKit2
//

import Foundation

public protocol IUnsafeString {
    
    func `unsafe`< Result >(_ block: (OpaquePointer?, UInt, String.Encoding) -> Result) -> Result
    
}

extension Swift.String : IUnsafeString {
    
    @inlinable
    public func unsafe< Result >(_ block: (OpaquePointer?, UInt, String.Encoding) -> Result) -> Result {
        return self.withCString({
            return block(OpaquePointer($0), UInt(self.count), .utf8)
        })
    }
    
}

extension Swift.StaticString : IUnsafeString {
    
    @inlinable
    public func unsafe< Result >(_ block: (OpaquePointer?, UInt, String.Encoding) -> Result) -> Result {
        return self.withUTF8Buffer({
            return block($0.baseAddress.flatMap({ OpaquePointer($0) }), UInt($0.count), .utf8)
        })
    }
    
}
