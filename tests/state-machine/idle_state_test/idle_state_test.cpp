#include "idle_state_test.hpp"

#include "../../stubs/stub_pos_context.hpp"

INLINE_FUNCTION void IdleStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString + "\n");
    std::cin.rdbuf(input.rdbuf());
    std::cin.clear();
}

void IdleStateTest::SetUp()
{
    posContext      = new MockContext();
    idleState       = new IdleState();
    transactionData = new TransactionData("Afonso's Supermarket");
}

void IdleStateTest::TearDown()
{
    delete idleState;
    delete posContext;
    delete transactionData;
}

TEST_F(IdleStateTest, enterState_exit)
{
    createCustomInputString("exit");

    Context* context = new StubPOSContext();

    ASSERT_EXIT({ idleState->enterState(*context); }, ::testing::ExitedWithCode(0), "");
}

TEST_F(IdleStateTest, enterState_invalidInput)
{
    createCustomInputString("invalidInput");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_DEATH({ idleState->enterState(*posContext); }, "");
}

TEST_F(IdleStateTest, processState_show)
{
    createCustomInputString("show");

    EXPECT_CALL(*posContext, getTransactionData()).Times(1).WillOnce(::testing::ReturnRef(*transactionData));
    idleState->enterState(*posContext);

    EXPECT_CALL(*posContext, transitionToState(StateType::Idle)).Times(1);
    idleState->processState(*posContext);
}

TEST_F(IdleStateTest, processState_clean)
{
    createCustomInputString("clean");

    EXPECT_CALL(*posContext, getTransactionData()).Times(1).WillOnce(::testing::ReturnRef(*transactionData));
    idleState->enterState(*posContext);

    EXPECT_CALL(*posContext, transitionToState(StateType::Idle)).Times(1);
    idleState->processState(*posContext);
}

TEST_F(IdleStateTest, processState_enter)
{
    createCustomInputString("");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));

    idleState->enterState(*posContext);

    std::istringstream input("validOperatorName");
    std::cin.rdbuf(input.rdbuf());

    EXPECT_CALL(*posContext, transitionToState(StateType::Ready)).Times(1);
    idleState->processState(*posContext);
}

INSTANTIATE_TEST_SUITE_P(
    IdleStateInputs,
    IdleStateParamTest,
    ::testing::Values("\n", "show", "clean"));

TEST_P(IdleStateParamTest, enterState_multipleValidInputs)
{
    const std::string& inputString = GetParam();

    createCustomInputString(inputString);

    EXPECT_CALL(*posContext, getTransactionData()).Times(1).WillOnce(::testing::ReturnRef(*transactionData));
    idleState->enterState(*posContext);
}