```c
class ControlBodyEditor : public Transform {
    CGENControl*      control;
    P4::ReferenceMap* refMap;
    P4::TypeMap*      typeMap;

 public:
    ControlBodyEditor(CGENControl* control, P4::ReferenceMap* refMap, P4::TypeMap* typeMap) :
    control(control), refMap(refMap), typeMap(typeMap)
    { CHECK_NULL(control); CHECK_NULL(refMap); CHECK_NULL(typeMap); setName("ControlBodyEditor");}
    const IR::Node* preorder(IR::MethodCallStatement* st) override;
    const IR::Node* preorder(IR::P4Table* t) override;
};

/////////////////////////////////////////////////
const IR::Node* ControlBodyEditor::preorder(IR::P4Table* table) {
    return nullptr;
}
const IR::Node* ControlBodyEditor::preorder(IR::MethodCallStatement* st) {
    auto mce = st->methodCall;
    auto mi = P4::MethodInstance::resolve(mce, refMap, typeMap);
    if (!mi->isApply())
        return st;
    auto am = mi->to<P4::ApplyMethod>();
    BUG_CHECK(am->object->is<IR::P4Table>(), "Expected table %1%", am->object);
    auto table = am->object->to<IR::P4Table>();
    if (table->name.name == control->ctbls[control->index].table->table->container->name.name) {
        std::cout << "editor apply: " << table->name.name << std::endl;
    } else {
        std::cout << "editor delete: " << table->name.name << std::endl;
        visit(table);
        return nullptr;
    }
    return st;
}
/////////// Use of editor is included below ///////////////////////
        ControlBodyEditor editor(this, program->refMap, program->typeMap);
        std::ostream* out;
        out = &std::cout;
        P4::ToP4 toP4(out, true, nullptr);
        index = 0;
        for (auto it : tables) {
            std::cout << "table: " << it.first << " index " << index << std::endl;
            ctbls[index].control = control->clone();
            ctbls[index].table = it.second;
            ctbls[index].control->body->apply(editor);
            auto node = ctbls[index].control->body->getNode();
            node->apply(toP4);
            index++;
        }

apply {
   pkt_filter4.apply();
   intermediate_upf_filter.apply();
   /* rest of code */
}

Change to:

apply {
   pkt_filter4.apply();
   /* rest of code */
}

apply {
   intermediate_upf_filter.apply();
   /* rest of code */
}
///////////////////////////////////
apply {
   /* code block 1 */
   if () {

   } else {
       pkt_filter4.apply();
       intermediate_upf_filter.apply();
   }
}

Change to:

apply {
   /* code block 1 */
   if () {

   } else {
       pkt_filter4.apply();
   }
}

apply {
   /* code block 1 */
   if () {

   } else {
       intermediate_upf_filter.apply();
   }
}
////////////////////////////////////
apply {
   /* code block 1 */
   if () {
       pkt_filter4.apply();
       intermediate_upf_filter.apply();
   } else {
     ;
   }
}

Change to:

apply {
   /* code block 1 */
   if () {
       pkt_filter4.apply();
   } else {
     ;
   }
}

apply {
   /* code block 1 */
   if () {
       intermediate_upf_filter.apply();
   } else {
     ;
   }
}
```
