//
//  KindKit2
//

import Foundation
import libkk2

public extension String {
    
    struct Range {
        
        public var raw: kk2_range_index_t
        
        public init(
            _ raw: kk2_range_index_t
        ) {
            self.raw = raw
        }
        
        public init(
            lower: UInt,
            upper: UInt
        ) {
            self.raw = .init(
                lower: lower,
                upper: upper
            )
        }
        
    }
    
}

public extension String.Range {
    
    @inlinable
    var lower: UInt {
        return self.raw.lower
    }
    
    @inlinable
    var upper: UInt {
        return self.raw.upper
    }

    @inlinable
    var count: UInt {
        return self.raw.upper - self.raw.lower
    }
    
    @inlinable
    var isEmpty: Bool {
        return self.count == 0
    }
    
}

extension String.Range : Equatable {
    
    public static func == (lhs: String.Range, rhs: String.Range) -> Bool {
        return lhs.lower == rhs.lower && lhs.upper == rhs.upper
    }
    
}
