#include "webfuse/adapter/impl/operation/close.h"
#include <gtest/gtest.h>

#include "webfuse/mocks/mock_fuse.hpp"
#include "webfuse/mocks/mock_operations_context.hpp"
#include "webfuse/mocks/mock_jsonrpc_proxy.hpp"

#include <gtest/gtest.h>

using webfuse_test::MockJsonRpcProxy;
using webfuse_test::MockOperationsContext;
using webfuse_test::FuseMock;
using testing::_;
using testing::Return;
using testing::StrEq;

TEST(wf_impl_operation_close, notify_proxy)
{
    MockJsonRpcProxy proxy;
    EXPECT_CALL(proxy, wf_jsonrpc_proxy_vnotify(_,StrEq("close"),StrEq("siii"),_)).Times(1);

    MockOperationsContext context;
    EXPECT_CALL(context, wf_impl_operations_context_get_proxy(_)).Times(1)
        .WillOnce(Return(reinterpret_cast<wf_jsonrpc_proxy*>(&proxy)));

    wf_impl_operations_context op_context;
    op_context.name = nullptr;
    FuseMock fuse;
    EXPECT_CALL(fuse, fuse_req_userdata(_)).Times(1).WillOnce(Return(&op_context));
    EXPECT_CALL(fuse, fuse_reply_err(_, 0)).Times(1).WillOnce(Return(0));

    fuse_req_t request = nullptr;
    fuse_ino_t inode = 1;
    fuse_file_info file_info;
    file_info.flags = 0;
    wf_impl_operation_close(request, inode, &file_info);
}

TEST(wf_impl_operation_close, fail_rpc_null)
{
    MockJsonRpcProxy proxy;
    EXPECT_CALL(proxy, wf_jsonrpc_proxy_vnotify(_,_,_,_)).Times(0);

    MockOperationsContext context;
    EXPECT_CALL(context, wf_impl_operations_context_get_proxy(_)).Times(1)
        .WillOnce(Return(nullptr));

    FuseMock fuse;
    EXPECT_CALL(fuse, fuse_req_userdata(_)).Times(1).WillOnce(Return(nullptr));
    EXPECT_CALL(fuse, fuse_reply_err(_, 0)).Times(1).WillOnce(Return(0));

    fuse_req_t request = nullptr;
    fuse_ino_t inode = 1;
    fuse_file_info * file_info = nullptr;
    wf_impl_operation_close(request, inode, file_info);
}
