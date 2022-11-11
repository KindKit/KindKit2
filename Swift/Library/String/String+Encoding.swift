//
//  KindKit2
//

import Foundation
import libkk2

public extension String {
    
    enum Encoding {
        
        case utf8
        
    }
    
}

public extension String.Encoding {
    
    @inlinable
    var raw: kk2_string_encoding_t {
        switch self {
        case .utf8: return kk2_string_encoding_utf8
        }
    }
    
    init(
        _ raw: kk2_string_encoding_t
    ) {
        switch raw {
        case kk2_string_encoding_utf8: self = .utf8
        default: fatalError()
        }
    }
    
}
