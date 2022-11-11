//
//  KindKit2
//

import Foundation
import libkk2

public final class String {
        
    public var raw: kk2_string_ct
    
    public init() {
        self.raw = kk2_string()
    }
    
    public init(_ raw: kk2_string_ct) {
        self.raw = raw
    }
    
    public init(move string: String) {
        self.raw = string.raw
        string.raw = kk2_string()
    }
    
    public init< Other : IUnsafeString >(_ other: Other) {
        self.raw = other.unsafe({ chars, count, encoding in
            kk2_string_with(
                kk2_alloc_default(),
                kk2_string_behaviour_default(),
                encoding.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            )
        })
    }
    
    deinit {
        kk2_string_free(&self.raw)
    }
        
    
}

extension String : IUnsafeString {
    
    @inlinable
    public func unsafe< Result >(_ block: (OpaquePointer?, UInt, String.Encoding) -> Result) -> Result {
        block(OpaquePointer(kk2_string_chars(&self.raw)), UInt(kk2_string_count(&self.raw)), self.encoding)
    }
    
}

extension String : IString {
    
    @inlinable
    public var encoding: String.Encoding {
        .init(kk2_string_encoding(&self.raw))
    }
    
    @inlinable
    public var capacity: UInt {
        .init(kk2_string_capacity(&self.raw))
    }
    
    @inlinable
    public var length: UInt {
        .init(kk2_string_length(&self.raw))
    }
    
    @inlinable
    public var count: UInt {
        .init(kk2_string_count(&self.raw))
    }
    
    @inlinable
    public var isEmpty: Bool {
        kk2_string_is_empty(&self.raw)
    }
    
    @inlinable
    public var startIndex: UInt {
        .init(kk2_string_start_index(&self.raw))
    }
    
    @inlinable
    public var endIndex: UInt {
        .init(kk2_string_end_index(&self.raw))
    }
    
    @inlinable
    public var range: String.Range {
        .init(kk2_string_range(&self.raw))
    }
    
    @inlinable
    public func `is`< Equal : IUnsafeString >(equal: Equal) -> Bool {
        equal.unsafe({ chars, count, _ in
            kk2_string_is_equal(
                &self.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            )
        })
    }
    
    @inlinable
    public func `is`< Prefix : IUnsafeString >(prefix: Prefix) -> Bool {
        prefix.unsafe({ chars, count, _ in
            kk2_string_is_prefix(
                &self.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            )
        })
    }
    
    @inlinable
    public func `is`< Suffix : IUnsafeString >(suffix: Suffix) -> Bool {
        suffix.unsafe({ chars, count, _ in
            kk2_string_is_suffix(
                &self.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            )
        })
    }
    
    @inlinable
    public func find< First : IUnsafeString >(first: First, in range: String.Range) -> String.Range {
        first.unsafe({ chars, count, _ in
            .init(kk2_string_find_start(
                &self.raw,
                range.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            ))
        })
    }
    
    @inlinable
    public func find< Last : IUnsafeString >(last: Last, in range: String.Range) -> String.Range {
        last.unsafe({ chars, count, _ in
            .init(kk2_string_find_end(
                &self.raw,
                range.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            ))
        })
    }
    
}

public extension String {
    
    func modify(_ block: (_ mutable: Mutable) -> Void) {
        block(Mutable(&self.raw))
    }
    
    func copy(_ block: (_ mutable: Mutable) -> Void) -> Self {
        var copy = kk2_string_with(self.raw.alloc, self.raw.behaviour, self.raw.encoding, .init(
            chars: kk2_string_chars(&self.raw),
            count: kk2_string_count(&self.raw)
        ))
        block(Mutable(&copy))
        return .init(copy)
    }
    
}
