#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <queuea/queuea.h>

TEST_CASE("Queuea is_empty", "[queuea]") {
	CHECK(QueueA().is_empty());
	//
	QueueA q;
	{
		QueueA q_copy(q);
		CHECK(q_copy.is_empty());
	}
	q.push(9);
	CHECK(!q.is_empty());
	{
		QueueA q_copy(q);
		CHECK(!q_copy.is_empty());
	}
	q.pop();
	CHECK(q.is_empty());
}

TEST_CASE("Queuea operator=", "[queuea]") {
	QueueA q, q_copy;
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
	QueueA q_empty;
	q_copy = q_empty;
	CHECK(q_copy.is_empty());
	q_empty = q_empty;
	CHECK(q_empty.is_empty());
}

TEST_CASE("Queuea top", "[queuea]") {
	QueueA q;
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

TEST_CASE("Queuea copy", "[queuea]") {
	QueueA q1, q2;

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