//
//  KindKit2
//

import Foundation
import libkk2

public extension String {
    
    struct Mutable {
        
        public var raw: kk2_string_pt
        
        @usableFromInline
        init(_ raw: kk2_string_pt) {
            self.raw = raw
        }
        
    }
    
}

extension String.Mutable : IUnsafeString {
    
    @inlinable
    public func unsafe< Result >(_ block: (OpaquePointer?, UInt, String.Encoding) -> Result) -> Result {
        block(OpaquePointer(kk2_string_chars(self.raw)), UInt(kk2_string_count(self.raw)), self.encoding)
    }
    
}

extension String.Mutable : IString {
    
    @inlinable
    public var encoding: String.Encoding {
        .init(kk2_string_encoding(self.raw))
    }
    
    @inlinable
    public var capacity: UInt {
        .init(kk2_string_capacity(self.raw))
    }
    
    @inlinable
    public var length: UInt {
        .init(kk2_string_length(self.raw))
    }
    
    @inlinable
    public var count: UInt {
        .init(kk2_string_count(self.raw))
    }
    
    @inlinable
    public var isEmpty: Bool {
        kk2_string_is_empty(self.raw)
    }
    
    @inlinable
    public var startIndex: UInt {
        .init(kk2_string_start_index(self.raw))
    }
    
    @inlinable
    public var endIndex: UInt {
        .init(kk2_string_end_index(self.raw))
    }
    
    @inlinable
    public var range: String.Range {
        .init(kk2_string_range(self.raw))
    }
    
    @inlinable
    public func `is`< Equal : IUnsafeString >(equal: Equal) -> Bool {
        equal.unsafe({ chars, count, _ in
            kk2_string_is_equal(
                self.raw,
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
                self.raw,
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
                self.raw,
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
                self.raw,
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
                self.raw,
                range.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            ))
        })
    }

}

extension String.Mutable : IMutableString {
    
    @inlinable
    public func clear() {
        kk2_string_free(self.raw)
    }
    
    @inlinable
    @discardableResult
    public func fit() -> Bool {
        return kk2_string_fit(self.raw)
    }
    
    @inlinable
    @discardableResult
    public func insert< Insert : IUnsafeString >(_ string: Insert, at index: UInt) -> Bool {
        string.unsafe({ chars, count, _ in
            kk2_string_insert(
                self.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                ),
                index
            )
        })
    }
    
    @inlinable
    @discardableResult
    public func prepend< Insert : IUnsafeString >(_ string: Insert) -> Bool {
        string.unsafe({ chars, count, _ in
            kk2_string_insert(
                self.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                ),
                kk2_string_start_index(self.raw)
            )
        })
    }
    
    @inlinable
    @discardableResult
    public func append< Insert : IUnsafeString >(_ string: Insert) -> Bool {
        string.unsafe({ chars, count, _ in
            kk2_string_insert(
                self.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                ),
                kk2_string_end_index(self.raw)
            )
        })
    }
    
    @inlinable
    @discardableResult
    public func remove(in range: String.Range) -> UInt {
        return kk2_string_remove_range(self.raw, range.raw)
    }
    
    @inlinable
    @discardableResult
    public func remove< Search : IUnsafeString >(first: Search, in range: String.Range) -> UInt {
        first.unsafe({ chars, count, _ in
            kk2_string_remove_first(
                self.raw,
                range.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            )
        })
    }
    
    @inlinable
    @discardableResult
    public func remove< Last : IUnsafeString >(last: Last, in range: String.Range) -> UInt {
        last.unsafe({ chars, count, _ in
            kk2_string_remove_last(
                self.raw,
                range.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            )
        })
    }
    
    @inlinable
    @discardableResult
    public func remove< All : IUnsafeString >(all: All, in range: String.Range) -> UInt {
        all.unsafe({ chars, count, _ in
            kk2_string_remove_all(
                self.raw,
                range.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            )
        })
    }
    
    @inlinable
    @discardableResult
    public func replace< To : IUnsafeString >(range: String.Range, to: To) -> Bool {
        to.unsafe({ chars, count, _ in
            kk2_string_replace_range(
                self.raw,
                range.raw,
                .init(
                    chars: kk2_string_char_cpt(chars),
                    count: kk2_size_t(count)
                )
            )
        })
    }
    
    @inlinable
    @discardableResult
    public func replace< First : IUnsafeString, To : IUnsafeString >(first: First, to: To, in range: String.Range) -> Bool {
        first.unsafe({ firstChars, firstCount, _ in
            to.unsafe({ toChars, toCount, _ in
                kk2_string_replace_first(
                    self.raw,
                    range.raw,
                    .init(
                        chars: kk2_string_char_cpt(firstChars),
                        count: kk2_size_t(firstCount)
                    ),
                    .init(
                        chars: kk2_string_char_cpt(toChars),
                        count: kk2_size_t(toCount)
                    )
                )
            })
        })
    }
    
    @inlinable
    @discardableResult
    public func replace< Last : IUnsafeString, To : IUnsafeString >(last: Last, to: To, in range: String.Range) -> Bool {
        last.unsafe({ lastChars, lastSize, _ in
            to.unsafe({ toChars, toCount, _ in
                kk2_string_replace_last(
                    self.raw,
                    range.raw,
                    .init(
                        chars: kk2_string_char_cpt(lastChars),
                        count: kk2_size_t(lastSize)
                    ),
                    .init(
                        chars: kk2_string_char_cpt(toChars),
                        count: kk2_size_t(toCount)
                    )
                )
            })
        })
    }
    
    @inlinable
    @discardableResult
    public func replace< All : IUnsafeString, To : IUnsafeString >(all: All, to: To, in range: String.Range) -> UInt {
        all.unsafe({ allChars, allCount, _ in
            to.unsafe({ toChars, toCount, _ in
                kk2_string_replace_all(
                    self.raw,
                    range.raw,
                    .init(
                        chars: kk2_string_char_cpt(allChars),
                        count: kk2_size_t(allCount)
                    ),
                    .init(
                        chars: kk2_string_char_cpt(toChars),
                        count: kk2_size_t(toCount)
                    )
                )
            })
        })
    }
    
}
