/***************************************************************************
 *  io/serving_request.cpp
 *
 *  Part of the STXXL. See http://stxxl.sourceforge.net
 *
 *  Copyright (C) 2002 Roman Dementiev <dementiev@mpi-sb.mpg.de>
 *  Copyright (C) 2008 Andreas Beckmann <beckmann@cs.uni-frankfurt.de>
 *
 *  Distributed under the Boost Software License, Version 1.0.
 *  (See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt)
 **************************************************************************/

#include <iomanip>
#include <stxxl/bits/io/serving_request.h>
#include <stxxl/bits/io/file.h>


__STXXL_BEGIN_NAMESPACE


serving_request::serving_request(
    const completion_handler & on_cmpl,
    file * f,
    void * buf,
    offset_type off,
    size_type b,
    request_type t) :
    request_with_state(on_cmpl, f, buf, off, b, t)
{
#ifdef STXXL_CHECK_BLOCK_ALIGNING
    // Direct I/O requires file system block size alignment for file offsets,
    // memory buffer addresses, and transfer(buffer) size must be multiple
    // of the file system block size
    check_alignment();
#endif
}

void serving_request::serve()
{
    check_nref();
    STXXL_VERBOSE2(
        "[" << static_cast<void *>(this) << "] serving_request::serve(): " <<
        buffer << " @ [" <<
        file_ << "|" << file_->get_allocator_id() << "]0x" <<
        std::hex << std::setfill('0') << std::setw(8) <<
        offset << "/0x" << bytes <<
        ((type == request::READ) ? " READ" : " WRITE"));

    try
    {
        file_->serve(this);
    }
    catch (const io_error & ex)
    {
        error_occured(ex.what());
    }

    check_nref(true);

    completed();
}

void serving_request::completed()
{
    STXXL_VERBOSE2("[" << static_cast<void *>(this) << "] serving_request::completed()");
    _state.set_to(DONE);
    request_with_state::completed();
    _state.set_to(READY2DIE);
}

const char * serving_request::io_type() const
{
    return file_->io_type();
}

__STXXL_END_NAMESPACE
// vim: et:ts=4:sw=4
