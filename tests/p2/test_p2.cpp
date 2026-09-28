// tests/p2/test_p2.cpp
//
// YOUR test suite goes here. At least 12 assert-based test cases — see
// spec §5 for the required categories and the sample test for the
// expected level of rigor.
//
// This file is a stub so the project builds out of the box; replace the
// body of main() with your own tests.

#include "core/conversation.h"
#include "core/message.h"
#include "core/sentinel_scanner.h"
#include "harness/harness.h"
#include "model/replay_client.h"
#include "model/scripted_client.h"

#include <cassert>

void empty_conversation_bounds_test() {
    Conversation conversation;
    bool pass = false;
    try{
        conversation.at(0);

    } catch(const std::out_of_range& x){
        pass = true;
    }
    assert(pass);
    assert(conversation.size() == 0);
    assert(conversation.begin() == nullptr);
}

void system_message_ordering_test(){
    Conversation conversation;
    Message testSystemMessage(Role::System, "Test message");
    conversation.append(testSystemMessage);
    Message testUserMessage(Role::User, "Hello");
    conversation.append(testUserMessage);
    Message testAssistantMessage(Role::Assistant, "Another test");
    conversation.append(testAssistantMessage);
    assert(conversation.at(0).role() == Role::System);
    assert(conversation.at(1).role() == Role::User);
    assert(conversation.at(2).role() == Role::Assistant);


}

void copy_constructor_test(){
    Conversation conversation;
    Message testSystemMessage(Role::System, "Test message");
    conversation.append(testSystemMessage);
    Message testUserMessage(Role::User, "Hello");
    conversation.append(testUserMessage);
    Message testAssistantMessage(Role::Assistant, "Another test");
    conversation.append(testAssistantMessage);
    Message testSystemMessage2(Role::System, "Test message 2");
    conversation.append(testSystemMessage2);
    Message testAssistantMessage2(Role::Assistant, "Another test 2");
    conversation.append(testAssistantMessage2);
    Conversation copyConversation = conversation;
    Message testUserMessage2(Role::User, "Hello world");
    copyConversation.append(testUserMessage2);
    assert(copyConversation.size() == 6);
    assert(copyConversation.at(0).role() == Role::System);
    assert(copyConversation.at(1).role() == Role::User);
    assert(copyConversation.at(2).role() == Role::Assistant);
    assert(copyConversation.begin() != conversation.begin());
    assert(conversation.size() == 5);
}

void rule_of_five_test(){
    Conversation conversation;
    Message testSystemMessage(Role::System, "Test message");
    conversation.append(testSystemMessage);
    Message testUserMessage(Role::User, "Hello");
    conversation.append(testUserMessage);
    Message testAssistantMessage(Role::Assistant, "Another test");
    conversation.append(testAssistantMessage);
    Message testSystemMessage2(Role::System, "Test message 2");
    conversation.append(testSystemMessage2);
    Message testAssistantMessage2(Role::Assistant, "Another test 2");
    conversation.append(testAssistantMessage2);
    const Message* startingPointer = conversation.begin();
    Conversation movedConversation = std::move(conversation);
    assert(movedConversation.begin() == startingPointer);
    assert(conversation.size() == 0);
    assert(conversation.begin() == nullptr);

    Conversation oldConversation;
    Message testSystemMessage3(Role::System, "Test message");
    oldConversation.append(testSystemMessage3);
    Message testUserMessage3(Role::User, "Hello");
    oldConversation.append(testUserMessage3);
    Message testAssistantMessage3(Role::Assistant, "Another test");
    oldConversation.append(testAssistantMessage3);
    Conversation newConversation;
    Message placeholderMessage(Role::User, "Placeholder");
    newConversation.append(placeholderMessage);
    newConversation = oldConversation;
    assert(newConversation.size() == 3);
    assert(newConversation.at(0).role() == Role::System);
    assert(newConversation.at(1).role() == Role::User);
    assert(newConversation.at(2).role() == Role::Assistant);
    Message extraMessage(Role::User, "hello");
    newConversation.append(extraMessage);
    assert(newConversation.size() == 4);
    assert(oldConversation.size() == 3);

    Conversation oldConversation2;
    Message testSystemMessage4(Role::System, "Test message 4");
    oldConversation2.append(testSystemMessage4);
    Message testAssistantMessage4(Role::Assistant, "Another test 4");
    oldConversation2.append(testAssistantMessage4);
    const Message* moveSourcePointer = oldConversation2.begin();
    Conversation newConversation2;
    Message tempMessage(Role::User, "Hello again bye");
    newConversation2.append(tempMessage);
    newConversation2 = std::move(oldConversation2);
    assert(newConversation2.begin() == moveSourcePointer);
    assert(newConversation2.size() == 2);
    assert(oldConversation2.size() == 0);
    assert(oldConversation2.begin() == nullptr);
}

void growth_behavior_test(){
    Conversation conversation;
    const Message* startingPointer0 = conversation.begin();
    assert(startingPointer0 == nullptr);
    assert(conversation.size() == 0);

    Message testSystemMessage(Role::System, "Test message");
    conversation.append(testSystemMessage);
    const Message* startingPointer1 = conversation.begin();
    assert(startingPointer1 != startingPointer0);
    assert(conversation.size() == 1);
    assert(conversation.at(0).role() == Role::System);
    assert(conversation.at(0).content() == "Test message");


    Message testUserMessage(Role::User, "Hello");
    conversation.append(testUserMessage);
    const Message* startingPointer2 = conversation.begin();
    assert(startingPointer2 != startingPointer1);
    assert(conversation.size() == 2);
    assert(conversation.at(0).role() == Role::System);
    assert(conversation.at(0).content() == "Test message");
    assert(conversation.at(1).role() == Role::User);
    assert(conversation.at(1).content() == "Hello");


    Message testAssistantMessage(Role::Assistant, "Another test");
    conversation.append(testAssistantMessage);
    const Message* startingPointer3 = conversation.begin();
    assert(startingPointer3 != startingPointer2);
    assert(conversation.size() == 3);
    assert(conversation.at(0).role() == Role::System);
    assert(conversation.at(0).content() == "Test message");
    assert(conversation.at(1).role() == Role::User);
    assert(conversation.at(1).content() == "Hello");
    assert(conversation.at(2).role() == Role::Assistant);
    assert(conversation.at(2).content() == "Another test");
    

    Message testSystemMessage2(Role::System, "Test message 2");
    conversation.append(testSystemMessage2);
    const Message* startingPointer4 = conversation.begin();
    assert(startingPointer4 == startingPointer3);
    assert(conversation.size() == 4);
    assert(conversation.at(0).role() == Role::System);
    assert(conversation.at(0).content() == "Test message");
    assert(conversation.at(1).role() == Role::User);
    assert(conversation.at(1).content() == "Hello");
    assert(conversation.at(2).role() == Role::Assistant);
    assert(conversation.at(2).content() == "Another test");
    assert(conversation.at(3).role() == Role::System);
    assert(conversation.at(3).content() == "Test message 2");


    Message testAssistantMessage2(Role::Assistant, "Another test 2");
    conversation.append(testAssistantMessage2);
    const Message* startingPointer5 = conversation.begin();
    assert(startingPointer5 != startingPointer4);
    assert(conversation.size() == 5);
    assert(conversation.at(0).role() == Role::System);
    assert(conversation.at(0).content() == "Test message");
    assert(conversation.at(1).role() == Role::User);
    assert(conversation.at(1).content() == "Hello");
    assert(conversation.at(2).role() == Role::Assistant);
    assert(conversation.at(2).content() == "Another test");
    assert(conversation.at(3).role() == Role::System);
    assert(conversation.at(3).content() == "Test message 2");
    assert(conversation.at(4).role() == Role::Assistant);
    assert(conversation.at(4).content() == "Another test 2");
}

void scanner_clean_test(){
    const std::string testSentinel = "<|end_conversation|>";
    SentinelScanner scanner(testSentinel);
    std::string testString = "Hello world hello hi ok goodbye";
    SentinelScanner::Out output = scanner.feed(testString);
    SentinelScanner::Out output2 = scanner.flush();
    assert(output.sentinel_found == false);
    assert(output2.sentinel_found == false);
    assert(output.safe_text + output2.safe_text == testString);
}

void scanner_split_boundary_test() {
    const std::string test = "Goodbye.<|end_conversation|>";
    const std::string sentinel = "<|end_conversation|>";
    for (std::size_t split = 0; split <= test.size(); split++) {
        SentinelScanner scanner(sentinel);
        SentinelScanner::Out output1 = scanner.feed(test.substr(0, split));
        SentinelScanner::Out output2 = scanner.feed(test.substr(split));
        bool found = false;
        if(output1.sentinel_found || output2.sentinel_found){
            found = true;
        } else {
            found = false;
        }
        assert(found);
        assert(output1.safe_text + output2.safe_text == "Goodbye.");
    }
}

void scanner_false_alarm_test(){
    const std::string sentinel = "<|end_conversation|>";
    SentinelScanner scanner(sentinel);
    std::string testString = "Hello world <|end_world|>";
    SentinelScanner::Out output1 = scanner.feed(testString);
    SentinelScanner::Out output2 = scanner.flush();
    assert(output1.sentinel_found == false);
    assert(output2.sentinel_found == false);
    assert(output1.safe_text + output2.safe_text == testString);
}

void scanner_bounded_memory_test(){
    const std::string sentinel = "<|end_conversation|>";
    SentinelScanner scanner(sentinel);
    const std::string testString = "<|end_conv";
    int i = 0;
    while(i < (4*1024*1024)){
        for(std::size_t y = 0; y < testString.size(); y++){
            char x = testString[y];
            SentinelScanner::Out output = scanner.feed(std::string(1, x));
            assert(output.sentinel_found == false);
            assert(scanner.pendingSize() <= sentinel.size() - 1);
            i++;
        }
    }
}

int main() {
    // TODO: write your tests here.
    empty_conversation_bounds_test();
    system_message_ordering_test();
    copy_constructor_test();
    rule_of_five_test();
    growth_behavior_test();
    scanner_clean_test();
    scanner_split_boundary_test();
    scanner_false_alarm_test();
    scanner_bounded_memory_test();
    return 0;
}


