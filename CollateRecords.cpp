#include <iostream>
#include <map>
#include <string>
#include <vector>

class CollateRecords
{
    public :
        // Credits to Pavel Minaev http://stackoverflow.com/users/111335/pavel-minaev
        // from http://stackoverflow.com/questions/1500208/nested-stdmaps
        struct NestedMap ;
        struct NestedMap : std::map< std::string, NestedMap* > {} ;

        void start() ;
        void display( NestedMap* collatedrec ) ;
        std::vector< std::map< std::string, std::string > > makeRecords() ;
        NestedMap* groupMap( std::map< std::string, std::string >, 
                NestedMap* grouped, std::vector< std::string > ) ;
        NestedMap* createGroups( std::map< std::string, std::string >, 
                std::vector< std::string >, NestedMap* head, std::string keyprev ) ;
};

std::vector< std::map< std::string, std::string > > CollateRecords :: makeRecords()
{
    std::map< std::string, std::string > rec1 ;
    rec1[ "name" ] = "obj-1" ; rec1[ "status" ] = "up" ; rec1[ "region" ] = "us" ;
    
    std::map< std::string, std::string > rec2 ;
    rec2[ "name" ] = "obj-2" ; rec2[ "status" ] = "down" ; rec2[ "region" ] = "eu" ;

    std::map< std::string, std::string > rec3 ;
    rec3[ "name" ] = "obj-3" ; rec3[ "status" ] = "up" ; rec3[ "region" ] = "eu" ;

    std::map< std::string, std::string > rec4 ;
    rec4[ "name" ] = "obj-4" ; rec4[ "status" ] = "down" ; rec4[ "region" ] = "us" ;

    std::vector< std::map< std::string, std::string > > map_records ;
    map_records.push_back( rec1 ) ; map_records.push_back( rec2 ) ;
    map_records.push_back( rec3 ) ; map_records.push_back( rec4 ) ;

    return map_records ;
}

CollateRecords::NestedMap* CollateRecords :: createGroups(
        std::map< std::string, std::string > record, 
        std::vector< std::string > keys, NestedMap* head, std::string keyprev )
{
    NestedMap* temp = head ;
    while( !keys.empty() )
    {
        std::string key = keys.front() ;
        NestedMap* ptr = new NestedMap ;
        keys.erase( keys.begin() ) ;
        ( *ptr )[ record[ key ] ] = NULL ;
        ( *temp )[ record[ keyprev ] ] = ptr ;
        keyprev = key ;
        temp = ptr ;
        delete ptr ;
    }
    NestedMap* nm = new NestedMap ;
    for( std::map< std::string, std::string >::iterator it
            = record.begin() ; it != record.end() ; ++it )
    {
        NestedMap* temp = new NestedMap ;
        ( *nm )  [ it -> first ]  = temp ;
        ( *temp )[ it -> second ] = NULL ;
    }
    ( *temp )[ record[ keyprev ] ] = nm ;
    return head ;
}

CollateRecords::NestedMap* CollateRecords :: groupMap(
        std::map< std::string, std::string > record, NestedMap* grouped, 
        std::vector< std::string > keys )
{
    if( grouped == NULL )
    {
        grouped = new NestedMap ;
        std::string keyprev = keys.front() ;
        keys.erase( keys.begin() ) ;
        ( *grouped )[ record[ keyprev ] ] = NULL ;
        grouped = createGroups( record, keys, grouped, keyprev ) ;
    }
    else
    {
        NestedMap* temp = grouped ;
        while( !keys.empty() )
        {
            std::string keyprev = keys.front() ;
            keys.erase( keys.begin() ) ;
            if( temp->end() ==  temp->find( record[ keyprev ] ) )
            {
                ( *temp )[ record[ keyprev ] ] = NULL ; 
                temp = createGroups( record, keys, temp, keyprev ) ;
                break ;
            }
            else
            {
                temp = ( *temp )[ record[ keyprev ] ] ;
            }
        }
    }
    return grouped ;
}

void CollateRecords :: display( NestedMap* grpby )
{
    std::vector< std::pair< std::string, NestedMap* > > recstack ;
    for( std::map< std::string, NestedMap* >::iterator it = grpby->begin() ;
            it != grpby->end() ; ++it )
    {
        recstack.push_back( *it ) ;
        std::cout << it -> first << std::endl ;
    }
    while( !recstack.empty() )
    {
        std::pair< std::string, NestedMap* > KV = recstack.back() ;
        std::cout << KV.first << std::endl ;
        recstack.pop_back() ;
        if( KV.second != NULL )
        {
            for( std::map< std::string, NestedMap* >::iterator it = 
                    KV.second -> begin() ; it != KV.second -> end() ; ++it )
            {
                recstack.push_back( *it ) ;
            }
        }
    }
}

void CollateRecords :: start()
{
    // Get the records made. And store them in map_records.
    std::vector< std::map< std::string, std::string > > 
        map_records = makeRecords() ;

    // Here the keys are hard coded. However, the keys can be accepted as
    // a vector of strings, from some called function.
    std::vector< std::string > keys ;
    keys.push_back( "region" ) ;
    keys.push_back( "status" ) ;

    NestedMap* grpby = new NestedMap ;
    grpby = NULL ;
    for( std::vector< std::map< std::string, std::string > >::iterator
            it = map_records.begin() ; it != map_records.end() ; ++it )
    {
        grpby = groupMap( *it, grpby, keys ) ;
    }
    // display( grpby ) ;
}

int main()
{
    CollateRecords C ;
    C.start() ;
    return 0 ;
}
