#include <gtest/gtest.h>

#include <mu_coin_qt/qt.hpp>
#include <thread>
#include <QTest>

TEST (client, construction)
{
    mu_coin::system system (1, 24000, 25000, 1);
    int argc (0);
    QApplication application (argc, nullptr);
    mu_coin_qt::client client (application, *system.clients [0]);
}

TEST (client, main)
{
    mu_coin::system system (1, 24000, 25000, 1);
    int argc (0);
    QApplication application (argc, nullptr);
    mu_coin_qt::client client (application, *system.clients [0]);
    ASSERT_EQ (client.entry_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.send_coins, Qt::LeftButton);
    ASSERT_EQ (client.send_coins_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.send_coins_back, Qt::LeftButton);
    ASSERT_EQ (client.entry_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.show_wallet, Qt::LeftButton);
    ASSERT_EQ (client.wallet_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.wallet_back, Qt::LeftButton);
    ASSERT_EQ (client.entry_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.settings, Qt::LeftButton);
    ASSERT_EQ (client.settings_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.settings_change_password_button, Qt::LeftButton);
    ASSERT_EQ (client.password_change.window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.password_change.back, Qt::LeftButton);
    ASSERT_EQ (client.settings_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.settings_back, Qt::LeftButton);
    ASSERT_EQ (client.entry_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.show_ledger, Qt::LeftButton);
    ASSERT_EQ (client.ledger_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.ledger_back, Qt::LeftButton);
    ASSERT_EQ (client.entry_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.show_peers, Qt::LeftButton);
    ASSERT_EQ (client.peers_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.peers_back, Qt::LeftButton);
    ASSERT_EQ (client.entry_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.show_log, Qt::LeftButton);
    ASSERT_EQ (client.log_window, client.main_stack->currentWidget ());
    QTest::mouseClick (client.log_back, Qt::LeftButton);
    ASSERT_EQ (client.entry_window, client.main_stack->currentWidget ());
}

TEST (client, password_change)
{
    mu_coin::system system (1, 24000, 25000, 1);
    int argc (0);
    QApplication application (argc, nullptr);
    mu_coin_qt::client client (application, *system.clients [0]);
    QTest::mouseClick (client.settings, Qt::LeftButton);
    QTest::mouseClick (client.settings_change_password_button, Qt::LeftButton);
    ASSERT_NE (client.client_m.wallet.hash_password ("1"), client.client_m.wallet.password);
    QTest::keyClicks (client.password_change.password, "1");
    QTest::keyClicks (client.password_change.retype, "1");
    QTest::mouseClick (client.password_change.change, Qt::LeftButton);
    ASSERT_EQ (client.client_m.wallet.hash_password ("1"), client.client_m.wallet.password);
    ASSERT_EQ ("", client.password_change.password->text ());
    ASSERT_EQ ("", client.password_change.retype->text ());
}

TEST (client, password_nochange)
{
    mu_coin::system system (1, 24000, 25000, 1);
    int argc (0);
    QApplication application (argc, nullptr);
    mu_coin_qt::client client (application, *system.clients [0]);
    QTest::mouseClick (client.settings, Qt::LeftButton);
    QTest::mouseClick (client.settings_change_password_button, Qt::LeftButton);
    ASSERT_EQ (client.client_m.wallet.hash_password (""), client.client_m.wallet.password);
    QTest::keyClicks (client.password_change.password, "1");
    QTest::keyClicks (client.password_change.retype, "2");
    QTest::mouseClick (client.password_change.change, Qt::LeftButton);
    ASSERT_EQ (client.client_m.wallet.hash_password (""), client.client_m.wallet.password);
    ASSERT_EQ ("1", client.password_change.password->text ());
    ASSERT_EQ ("2", client.password_change.retype->text ());
}