#pragma once

#include <atomic>
#include <memory>
#include <functional>
#include <utility>

// template<typename T>
// class lock_free_queue
// {
// private:

//     struct node;
//     struct counted_node_ptr
//     {
//         int external_count;
//         node* ptr;
//     };
//     std::atomic<counted_node_ptr> head;
//     std::atomic<counted_node_ptr> tail;
    
//     struct node_counter
//     {
//         unsigned internal_count:30;
//         unsigned external_counters:2;
//     };

//     struct node
//     {
//         std::atomic<T*> data;
//         std::atomic<node_counter> count;
//         counted_node_ptr next;
//         node()
//         {
//             node_counter new_count;
//             new_count.internal_count=0;
//             new_count.external_counters=2;
//             count.store(new_count);
//             next.ptr=nullptr;
//             next.external_count=0;
//         }
//     };

//     void set_new_tail(counted_node_ptr &old_tail,
//                       counted_node_ptr const &new_tail)
//     {
//         node* const current_tail_ptr=old_tail.ptr;
//         while(!tail.compare_exchange_weak(old_tail,new_tail) &&
//               old_tail.ptr==current_tail_ptr);
//         if(old_tail.ptr==current_tail_ptr)
//             free_external_counter(old_tail);
//         else
//             current_tail_ptr->release_ref();
//     }
// public:
//     void push(T new_value)
//     {
//         std::unique_ptr<T> new_data(new T(new_value));
//         counted_node_ptr new_next;
//         new_next.ptr=new node;
//         new_next.external_count=1;
//         counted_node_ptr old_tail=tail.load();
//         for(;;)
//         {
//             increase_external_count(tail,old_tail);
//             T* old_data=nullptr;
//             if(old_tail.ptr->data.compare_exchange_strong(
//                    old_data,new_data.get()))
//             {
//                 counted_node_ptr old_next={0};
//                 if(!old_tail.ptr->next.compare_exchange_strong(
//                        old_next,new_next))
//                 {
//                     delete new_next.ptr;
//                     new_next=old_next;
//                 }
//                 set_new_tail(old_tail, new_next);
//                 new_data.release();
//                 break;
//             }
//             else
//             {
//                 counted_node_ptr old_next={0};
//                 if(old_tail.ptr->next.compare_exchange_strong(
//                        old_next,new_next))
//                 {
//                     old_next=new_next;
//                     new_next.ptr=new node;
//                 }
//                 set_new_tail(old_tail, old_next);
//             }
//         }
//     }

//     std::unique_ptr<T> pop()
//     {
//         counted_node_ptr old_head=head.load(std::memory_order_relaxed);
//         for(;;)
//         {
//             increase_external_count(head,old_head);
//             node* const ptr=old_head.ptr;
//             if(ptr==tail.load().ptr)
//             {
//                 return std::unique_ptr<T>();
//             }
//             counted_node_ptr next=ptr->next.load();
//             if(head.compare_exchange_strong(old_head,next))
//             {
//                 T* const res=ptr->data.exchange(nullptr);
//                 free_external_counter(old_head);
//                 return std::unique_ptr<T>(res);
//             }
//             ptr->release_ref();
//         }
//     }
// };
