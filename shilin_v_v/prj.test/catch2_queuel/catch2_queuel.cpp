#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <queuel/queuel.h>

TEST_CASE("Queuea is_empty", "[queuel]") {
	CHECK(QueueL().is_empty());
	//
	QueueL q;
	{
		QueueL q_copy(q);
		CHECK(q_copy.is_empty());
	}
	q.push(9);
	CHECK(!q.is_empty());
	{
		QueueL q_copy(q);
		CHECK(!q_copy.is_empty());
	}
	q.pop();
	CHECK(q.is_empty());
}

TEST_CASE("Queuea operator=", "[queuel]") {
	QueueL q, q_copy;
	q_copy = q;
	CHECK(q_copy.is_empty());
	//
	q.push(9);
	q_copy = q;
	CHECK(!q_copy.is_empty());
	//
	q_copy = q_copy;
	CHECK(!q_copy.is_empty());
	// create empty queue
	QueueL q_empty;
	q_copy = q_empty;
	CHECK(q_copy.is_empty());
	q_empty = q_empty;
	CHECK(q_empty.is_empty());
}

TEST_CASE("Queuea top", "[queuel]") {
	QueueL q;
	q.push(9);
	CHECK(q.top() == 9);
	q.pop();
	CHECK(q.is_empty());
	CHECK_THROWS(q.top());
	//
	q.push(1); q.push(2); q.push(3);
	CHECK(q.top() == 1);
	q.pop();
	CHECK(q.top() == 2);
	q.pop();
	CHECK(q.top() == 3);
	q.pop();
	CHECK_THROWS(q.top());
	//
	q.push(1); q.push(2); q.push(3);
	q.pop();
	q.push(4);
	q.pop();
	q.push(5);
	q.pop();
	CHECK(q.top() == 4);
	CHECK(!q.is_empty());
	q.pop();
	CHECK(q.top() == 5);
	q.pop();
	CHECK_THROWS(q.top());
}

TEST_CASE("Queuea copy", "[queuel]") {
	QueueL q1, q2;

	q1.push(1); q1.push(2); q1.push(3);
	q2.push(4); q2.push(5); q2.push(6); q2.push(7);

	SECTION("Copy larger to small") {
		q1 = q2;
		while (!q1.is_empty() && !q2.is_empty()) {
			CHECK(q1.top() == q2.top());
			q1.pop();
			if (!q1.is_empty()) {
				CHECK(q1.top() != q2.top());
			}
			q2.pop();
			if (!q1.is_empty() && !q2.is_empty()) {
				CHECK(q1.top() == q2.top());
			}
		}
		CHECK(q1.is_empty());
		CHECK(q2.is_empty());
	}

	q1.push(1); q1.push(2); q1.push(3);
	q2.push(4); q2.push(5); q2.push(6); q2.push(7);

	SECTION("Copy smaller to large") {
		q2 = q1;
		while (!q1.is_empty() && !q2.is_empty()) {
			CHECK(q1.top() == q2.top());
			q1.pop();
			if (!q1.is_empty()) {
				CHECK(q1.top() != q2.top());
			}
			q2.pop();
			if (!q1.is_empty() && !q2.is_empty()) {
				CHECK(q1.top() == q2.top());
			}
		}
		CHECK(q1.is_empty());
		CHECK(q2.is_empty());
	}
}

TEST_CASE("Queuea push", "[queuel]") {
	QueueL q;

	q.push(1); q.push(2); q.push(3); q.push(4); q.push(5); q.push(6);
	// 1 2 3 4 5 6
	q.pop(); q.pop(); q.pop();
	//       4 5 6
	q.push(7); q.push(8); q.push(9);

	SECTION("Push when iHead = 0"){
		QueueL q_copy(q);
		CHECK(q_copy.top() == 4);
		q_copy.pop();
		CHECK(q_copy.top() == 5);
		q_copy.pop();
		CHECK(q_copy.top() == 6);
		q_copy.pop();
		CHECK(q_copy.top() == 7);
		q_copy.pop();
		CHECK(q_copy.top() == 8);
		q_copy.pop();
		CHECK(q_copy.top() == 9);
	}

	q.push(10);

	SECTION("Push when iHead > 0"){
		QueueL q_copy(q);
		CHECK(q_copy.top() == 4);
		q_copy.pop();
		CHECK(q_copy.top() == 5);
		q_copy.pop();
		CHECK(q_copy.top() == 6);
		q_copy.pop();
		CHECK(q_copy.top() == 7);
		q_copy.pop();
		CHECK(q_copy.top() == 8);
		q_copy.pop();
		CHECK(q_copy.top() == 9);
		q_copy.pop();
		CHECK(q_copy.top() == 10);
	}

}